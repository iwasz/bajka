/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
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

#include "Events.h"
#include "App.h"
#include "../view/draw/Primitives.h"
#include "../model/IGroup.h"
#include "../tween/Manager.h"
#include "../events/types/UpdateEvent.h"
#include "../events/EventIdex.h"
#include "../events/PointerInsideIndex.h"
#include "../events/IDispatcher.h"

#include "../dependencies/GraphicsService.h"
#include "../dependencies/TimeService.h"
#include "../dependencies/OpenGlService.h"
#include "../dependencies/OpenGlCommonService.h"

#ifdef USE_SDL
#include <SDL.h>
#include <SDL_ttf.h>
#endif

/****************************************************************************/

Util::App *app ()
{
        return Util::App::instance ();
}

/****************************************************************************/

Util::Config *config ()
{
        return Util::App::instance ()->getConfig ().get ();
}

/****************************************************************************/

Util::ModelManager *manager ()
{
        return Util::App::instance ()->getManager ().get ();
}

/****************************************************************************/

namespace Util {
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace E = Event;

/**
 * pimpl
 */
struct Impl {

        Impl () : model (NULL), dropIteration_ (false) {}

        Ptr <Config> config;
        Ptr <Event::DispatcherList> dispatchers;
        Ptr <ModelManager> manager;

        Model::IModel *model;
        Event::EventIndex eventIndex;
        Event::PointerInsideIndex pointerInsideIndex;

        bool dropIteration_;
        Event::UpdateEvent updateEvent;
};

App *App::instance_ = NULL;

/****************************************************************************/

App::App () : impl (new Impl) {}
App::~App () { delete impl; }

/****************************************************************************/

App *App::instance ()
{
        assertThrow (instance_, "!instance_")
        return instance_;
}

/****************************************************************************/

void App::init ()
{
        int requestedResX = impl->config->getResX ();
        int requestedResY = impl->config->getResY ();

        View::GraphicsService::init (impl->config->getFullScreen (),
                                       &requestedResX,
                                       &requestedResY,
                                       impl->config->getWindowCaption (),
                                       impl->config->getShowSystemCursor ());


        View::OpenGlService::init (requestedResX, requestedResY);

        srand (time (NULL));
        Tween::init ();
}

/****************************************************************************/
#define checkBreak() { if (impl->dropIteration_) { break; } }
#define checkContinue() { if (impl->dropIteration_) { continue; } }

void App::loop ()
{
        bool done = false;

        if (!impl->model) {
        	throw InitException ("App has no model.");
        }

        uint32_t lastMs = Util::TimeService::getCurrentMs ();

        if (!impl->dispatchers) {
                impl->dispatchers = boost::make_shared <Event::DispatcherList> ();
        }

        if (!impl->model) {
                throw Util::RuntimeException ("App::loop : model == NULL.");
        }

#if 0
        int second = 0, frames = 0;
#endif

        View::Color const &clearColor = impl->config->getClearColor ();

        while (!done) {

                impl->dropIteration_ = false;
                uint32_t currentMs = Util::TimeService::getCurrentMs ();
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

                View::OpenGlCommonService::clear (clearColor);

                // Run models, views and controllers.
                // Generuj eventy.
                for (Event::DispatcherList::const_iterator i = impl->dispatchers->begin (); i != impl->dispatchers->end (); i++) {
                        (*i)->run (impl->model, impl->eventIndex, &impl->pointerInsideIndex);
                        checkBreak ();
                }

//                checkContinue ();
                impl->updateEvent.setDeltaMs (deltaMs);
                impl->model->update (&impl->updateEvent);
//                checkContinue ();

#if USE_CHIPMUNK
                // Run chipmunk
                if (Model::Space::getSpace ()) {
                        cpSpaceStep (Model::Space::getSpace (), 1.0 / 60.0);
                }
#endif

                Tween::Manager::getMain ()->update (deltaMs);
//                checkContinue ();

                // swap buffers to display, since we're double buffered.
                View::GraphicsService::swapBuffers ();

                // Tak śmiga, że damy delay
                Util::TimeService::delayMs (17); // 60fps
        }
}

/****************************************************************************/

void App::destroy ()
{
#ifdef USE_SDL
        TTF_Quit ();
        SDL_Quit ();
#endif
	Tween::free ();
}

/****************************************************************************/

Ptr <Config> App::getConfig () const
{
        return impl->config;
}

/****************************************************************************/

void App::setConfig (Ptr <Config> b)
{
        impl->config = b;
}

/****************************************************************************/

Model::IModel *App::getModel () const
{
        return impl->model;
}

/****************************************************************************/

void App::setModel (Model::IModel *m)
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

/****************************************************************************/

Ptr <ModelManager> App::getManager ()
{
        return impl->manager;
}

/****************************************************************************/

void App::setManager (Ptr <ModelManager> m)
{
        impl->manager = m;
        impl->manager->setApp (this);
}

/****************************************************************************/

Ptr <Event::DispatcherList> App::getDispatchers () const
{
        return impl->dispatchers;
}

/****************************************************************************/

void App::setDispatchers (Ptr <Event::DispatcherList> d)
{
        impl->dispatchers = d;

        for (Event::DispatcherList::const_iterator i = impl->dispatchers->begin (); i != impl->dispatchers->end (); i++) {
                (*i)->setApp (this);
        }
}

/****************************************************************************/

void App::reset ()
{
        dropIteration ();

        impl->eventIndex.clear ();
        impl->pointerInsideIndex.clear ();

        for (Event::DispatcherList::const_iterator i = impl->dispatchers->begin (); i != impl->dispatchers->end (); i++) {
                (*i)->reset ();
        }
}

/****************************************************************************/

void App::dropIteration ()
{
        impl->dropIteration_ = true;
}

/****************************************************************************/

bool App::getDropIteration () const
{
        return impl->dropIteration_;
}

} // Nam
