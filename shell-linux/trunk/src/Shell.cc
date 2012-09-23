/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>
#include <cstdlib>
#include <container/Container.h>
#include <container/ContainerFactory.h>
#include <container/inputFormat/compact/CompactMetaService.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#include "Shell.h"
#include "geometry/Point.h"
#include "geometry/LineString.h"
#include "events/Events.h"
#include "events/PointerInsideIndex.h"
#include "util/Config.h"
#include "util/Exceptions.h"
#include "GraphicsService.h"
#include "OpenGlService.h"
#include "Platform.h"
#include "util/ReflectionMacros.h"
#include "tween/Manager.h"
#include "EventDispatcher.h"
#include "model/IGroup.h"
#include "model/layout/Align.h"
#include "model/layout/LinearGroup.h"

using namespace Container;
using Reflection::Manager;
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace E = Event;
namespace U = Util;

/****************************************************************************/

Shell Shell::instance_;

Util::Config *config () { return shell ()->getConfig (); }
Util::IShell *shell () { return &Shell::instance_; }

/****************************************************************************/

/**
 * pimpl
 */
struct Impl {

        Impl () : config (NULL),
                model (NULL),
                dropIteration_ (false),
                loopActive (true) {}

        U::Config *config;
        Model::IModel *model;
        Event::EventIndex eventIndex;
        Event::PointerInsideIndex pointerInsideIndex;
        EventDispatcher dispatcher;

        bool dropIteration_;
        bool loopActive;
        Event::UpdateEvent updateEvent;
};

/****************************************************************************/

Shell::Shell () : impl (new Impl) {}
Shell::~Shell () { delete impl; }

/****************************************************************************/

int Shell::run (Util::ShellConfig const &cfg)
{
        try {
                /* Initialize SDL for video output */
                if (SDL_Init (SDL_INIT_VIDEO) < 0) {
                        throw U::InitException ("Unable to initialize SDL : " + std::string (SDL_GetError ()));
                }

                if (TTF_Init () < 0) {
                        throw U::InitException ("TTF_Init failed");
                }

                {
                        Ptr <MetaContainer> metaContainer = CompactMetaService::parseFile (cfg.definitionFile);
                        Ptr <BeanFactoryContainer> container = ContainerFactory::create (metaContainer, true);

                        container->addConversion (typeid (Geometry::Point), Geometry::stringToPointVariant);
                        container->addConversion (typeid (Geometry::LineString), Geometry::stringToLineStringVariant);
                        container->addConversion (typeid (Model::HAlign), Model::stringToHAlign);
                        container->addConversion (typeid (Model::VAlign), Model::stringToVAlign);
                        container->addConversion (typeid (Model::HGravity), Model::stringToHGravity);
                        container->addConversion (typeid (Model::VGravity), Model::stringToVGravity);
                        container->addConversion (typeid (Model::LinearGroup::Type), Model::stringToLinearGroupType);

                        ContainerFactory::init (container.get (), metaContainer.get ());
                        impl->config = vcast <U::Config *> (container->getBean ("config"));
                        overrideConfig (cfg);
                        setModel (impl->config->model);

                        init ();
                        loop ();
                        destroy ();
                }

                TTF_Quit ();
                SDL_Quit ();
        }
        catch (Core::Exception const &e) {
                std::cerr << "Exception caught : \n" << e.getMessage () << std::endl;
                return EXIT_FAILURE;
        }
        catch (std::exception const &e) {
                std::cerr << "exception caught : " << e.what () << std::endl;
                return EXIT_FAILURE;
        }
        catch (...) {
                std::cerr << "Unknown exception." << std::endl;
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

/****************************************************************************/

#define checkBreak() { if (impl->dropIteration_) { break; } }
#define checkContinue() { if (impl->dropIteration_) { continue; } }

/****************************************************************************/
void Shell::loop ()
{
        if (!impl->model) {
                throw U::InitException ("App has no model.");
        }

        uint32_t lastMs = getCurrentMs ();

#if 0
        int second = 0, frames = 0;
#endif

        int loopDelayMs = impl->config->loopDelayMs;

        while (impl->loopActive) {

                impl->dropIteration_ = false;
                uint32_t currentMs = getCurrentMs ();
                int deltaMs = currentMs - lastMs;
                lastMs = currentMs;

#if 0
                second += deltaMs;
                ++frames;

                if (second >= 1000) {
                        std::cerr << "fps=" << frames << std::endl;
                        frames = second = 0;
                }
#endif


                // Run models, views and controllers.
                // Generuj eventy.
                impl->dispatcher.pollAndDispatch (impl->model, impl->eventIndex, &impl->pointerInsideIndex);
                checkContinue ();

//                checkContinue ();
                impl->updateEvent.setDeltaMs (deltaMs);
                impl->model->update (&impl->updateEvent);
//                checkContinue ();

                Tween::Manager::getMain ()->update (deltaMs);
//                checkContinue ();

                // swap buffers to display, since we're double buffered.
                swapBuffers ();

                // Tak śmiga, że damy delay
                delayMs (loopDelayMs); // 60fps
        }
}

/****************************************************************************/

void Shell::init ()
{
        GraphicsService::updateConfig (impl->config);
        GraphicsService::init (impl->config);
        initOpenGl (impl->config);
        srand (time (NULL));
        Tween::init ();
}

/****************************************************************************/

void Shell::destroy ()
{
        Tween::free ();
}

/****************************************************************************/

void Shell::quit ()
{
        impl->loopActive = false;
}

/****************************************************************************/

void Shell::overrideConfig (Util::ShellConfig const &cfg)
{
        if (cfg.fullScreen) {
                impl->config->fullScreen = true;
        }

        if (cfg.showAABB) {
                impl->config->showAABB = true;
        }

        if (cfg.viewportWidth > 0) {
                impl->config->viewportWidth = cfg.viewportWidth;
        }

        if (cfg.viewportHeight > 0) {
                impl->config->viewportHeight = cfg.viewportHeight;
        }

        if (cfg.loopDelayMs > 0) {
                impl->config->loopDelayMs = cfg.viewportHeight;
        }
}

/****************************************************************************/

Model::IModel *Shell::getModel ()
{
        return impl->model;
}

/****************************************************************************/

void Shell::setModel (Model::IModel *m)
{
        impl->model = m;
        impl->eventIndex.clear ();
        impl->pointerInsideIndex.clear ();
        impl->eventIndex.add (0xFFFFu & ~Event::MOUSE_EVENTS, m);

        if (m->isGroup ()) {
                Model::IGroup *g = dynamic_cast <Model::IGroup *> (m);
                g->setIndices (&impl->eventIndex, &impl->pointerInsideIndex);
        }
}

//ModelManager *Shell::getManager ()
//{
//        return impl->manager;
//}
//
///****************************************************************************/
//
//void Shell::setManager (ModelManager *m)
//{
//        impl->manager = m;
//        impl->manager->setApp (this);
//}

void Shell::reset ()
{
        dropIteration ();

        impl->eventIndex.clear ();
        impl->pointerInsideIndex.clear ();
        impl->dispatcher.reset ();
}

/****************************************************************************/

void Shell::dropIteration ()
{
        impl->dropIteration_ = true;
}

/****************************************************************************/

bool Shell::getDropIteration () const
{
        return impl->dropIteration_;
}

Util::Config *Shell::getConfig ()
{
        return impl->config;
}
