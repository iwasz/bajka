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
#include <Container.h>
#include <ContainerFactory.h>
#include <inputFormat/compact/CompactMetaService.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#include "Shell.h"
#include "Point.h"
#include "geometry/LineString.h"
#include "Events.h"
#include "Config.h"
#include "PointerInsideIndex.h"
#include "Exceptions.h"
#include "Time.h"

using namespace Container;
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace E = Event;
namespace U = Util;

/**
 * pimpl
 */
struct Impl {

        Impl () : config (NULL),
                model (NULL),
                dropIteration_ (false) {}

        U::Config *config;
        Model::IModel *model;
        Event::EventIndex eventIndex;
        Event::PointerInsideIndex pointerInsideIndex;

        bool dropIteration_;
        Event::UpdateEvent updateEvent;
};

Shell::Shell () : impl (new Impl) {}
Shell::~Shell () { delete impl; }

int Shell::run (const char *file)
{
        try {

                /* Initialize SDL for video output */
                if (SDL_Init (SDL_INIT_VIDEO) < 0) {
                        throw U::InitException ("Unable to initialize SDL : " + std::string (SDL_GetError ()));
                }

                if (TTF_Init () < 0) {
                        throw U::InitException ("TTF_Init failed");
                }

                Ptr <MetaContainer> metaContainer = CompactMetaService::parseFile (file);
                Ptr <BeanFactoryContainer> container = ContainerFactory::create (metaContainer, true);
                container->addConversion (typeid (Geometry::Point), Geometry::stringToPointVariant);
                container->addConversion (typeid (Geometry::LineString), Geometry::stringToLineStringVariant);
                ContainerFactory::init (container.get (), metaContainer.get ());
                impl->config = vcast <U::Config *> (container->getBean ("config"));

                init ();
                loop ();
                destroy ();

                TTF_Quit ();
                SDL_Quit ();
        }
        catch (Core::Exception const &e) {
                std::cerr << "Exception caught : \n" << e.getMessage () << std::endl;
        }
        catch (std::exception const &e) {
                std::cerr << "exception caught : " << e.what () << std::endl;
        }
        catch (...) {
                std::cerr << "Unknown exception." << std::endl;
        }

        return EXIT_SUCCESS;
}

/****************************************************************************/

void Shell::loop ()
{
        bool done = false;

        if (!impl->model) {
                throw InitException ("App has no model.");
        }

        uint32_t lastMs = getCurrentMs ();

#if 0
        int second = 0, frames = 0;
#endif

        View::Color const &clearColor = impl->config->clearColor;
        int loopDelayMs = impl->config->loopDelayMs;

        while (!done) {

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


//                TODO to będzie widok/widget
//                View::clear (clearColor);

                // Run models, views and controllers.
                // Generuj eventy.
                for (Event::DispatcherList::const_iterator i = impl->dispatchers->begin (); i != impl->dispatchers->end (); i++) {
                        (*i)->pollAndDispatch (impl->model, impl->eventIndex, &impl->pointerInsideIndex);
                        checkBreak ();
                }

//                checkContinue ();
                impl->updateEvent.setDeltaMs (deltaMs);
                impl->model->update (&impl->updateEvent);
//                checkContinue ();

                // TODO a to też może być w jakimś kontrolerze, czy czymś, byle by nie było tu.
#ifdef USE_CHIPMUNK
                // Run chipmunk
                if (Model::Space::getSpace ()) {
                        cpSpaceStep (Model::Space::getSpace (), 1.0 / 60.0);
                }
#endif

                Tween::Manager::getMain ()->update (deltaMs);
//                checkContinue ();

                // swap buffers to display, since we're double buffered.
                swapBuffers ();

                // Tak śmiga, że damy delay
                delayMs (loopDelayMs); // 60fps
        }
}

