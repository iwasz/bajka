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

#include "GraphicsService.h"
#include "TimeService.h"
#include "OpenGlService.h"
#include "OpenGlCommonService.h"
#include "Logging.h"

#ifdef ANDROID
#include "android/AndroidEngine.h"
#endif


/****************************************************************************/

Util::App *app ()
{
        return Util::App::instance ();
}

/****************************************************************************/

Util::Config *config ()
{
        return Util::App::instance ()->getConfig ();
}

/****************************************************************************/

Util::ModelManager *manager ()
{
        return Util::App::instance ()->getManager ();
}

/****************************************************************************/

namespace Util {
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace E = Event;

struct NativeEvent {
        int type;
        void *data;
};

/*##########################################################################*/

/**
 * pimpl
 */
struct Impl {

        Impl () : config (NULL),
                dispatchers (NULL),
                manager (NULL),
                model (NULL),
		dropIteration_ (false) {}

        Config *config;
        Event::DispatcherList *dispatchers;
        ModelManager *manager;

        Model::IModel *model;
        Event::EventIndex eventIndex;
        Event::PointerInsideIndex pointerInsideIndex;

        bool dropIteration_;
        Event::UpdateEvent updateEvent;

#ifdef ANDROID
        AndroidEngine androidEngine;
        AndroidCmdEventSource cmdEventSource;
        AndroidInputEventSource inputEventSource;
#endif
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
                impl->dispatchers = new Event::DispatcherList ();
        }

#if 0
        int second = 0, frames = 0;
#endif

        View::Color const &clearColor = impl->config->getClearColor ();
        int loopDelayMs = impl->config->getLoopDelayMs ();

        while (!done) {

// TODO!!!
#ifdef ANDROID
                // Read all pending events.
                 int ident;
                 int events;
                 struct android_poll_source* source;

                 while ((ident = ALooper_pollAll (0, NULL, &events, (void**)&source)) >= 0) {

                     // Process this event.
                     if (source != NULL) {
                         source->process(impl->androidEngine.androidApp, source);
                     }

                     // If a sensor has data, process it now.
                     if (ident == LOOPER_ID_USER) {
                             for (EventSourceVector::iterator i = impl->eventSources.begin (); i != impl->eventSources.end (); ++i) {
                                     (*i)->poll ();
                             }
                     }

                     // Check if we are exiting.
                     if (impl->androidEngine.androidApp->destroyRequested != 0) {
//                         engine_term_display(&engine);
                         break;
                     }
                 }

                if (!impl->androidEngine.running) {
                        Util::TimeService::delayMs (17); // 60fps
                        continue;
                }
#endif

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
                        (*i)->pollAndDispatch (impl->model, impl->eventIndex, &impl->pointerInsideIndex);
                        checkBreak ();
                }

//                checkContinue ();
                impl->updateEvent.setDeltaMs (deltaMs);
                impl->model->update (&impl->updateEvent);
//                checkContinue ();

#ifdef USE_CHIPMUNK
                // Run chipmunk
                if (Model::Space::getSpace ()) {
                        cpSpaceStep (Model::Space::getSpace (), 1.0 / 60.0);
                }
#endif

                Tween::Manager::getMain ()->update (deltaMs);
//                checkContinue ();

                // swap buffers to display, since we're double buffered.
                View::GraphicsService::swapBuffers ();
// TODO
#ifdef ANDROID
                eglSwapBuffers (impl->androidEngine.display, impl->androidEngine.surface);
#endif

                // Tak śmiga, że damy delay
                Util::TimeService::delayMs (loopDelayMs); // 60fps
        }
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

//        for (EventSourceVector::iterator i = impl->eventSources.begin (); i != impl->eventSources.end (); ++i) {
//                (*i)->init (this);
//        }
}

/****************************************************************************/

void App::destroy ()
{
	Tween::free ();
}

/****************************************************************************/

Config *App::getConfig () const
{
        return impl->config;
}

/****************************************************************************/

void App::setConfig (Config *b)
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

ModelManager *App::getManager ()
{
        return impl->manager;
}

/****************************************************************************/

void App::setManager (ModelManager *m)
{
        impl->manager = m;
        impl->manager->setApp (this);
}

/****************************************************************************/

Event::DispatcherList *App::getDispatchers () const
{
        return impl->dispatchers;
}

/****************************************************************************/

void App::setDispatchers (Event::DispatcherList *d)
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

/****************************************************************************/
#ifdef ANDROID

void App::engineHandleCmd (int32_t cmd)
{
        NativeEvent native;
        native.data = &cmd;
//        impl->androidEngine.cmdDispatcher.dispatch (impl->model, impl->eventIndex, &impl->pointerInsideIndex, &cmd);
        impl->cmdEventSource.handle (this, &native);
}

/****************************************************************************/

int32_t App::engineHandleInput (AInputEvent* androidEvent)
{
//        return impl->androidEngine.inputDispatcher.dispatch (impl->model, impl->eventIndex, &impl->pointerInsideIndex, androidEvent);
}

/****************************************************************************/

Util::AndroidEngine const *App::getAndroidEngine () const
{
        return &impl->androidEngine;
}

/****************************************************************************/

Util::AndroidEngine *App::getAndroidEngine ()
{
        return &impl->androidEngine;
}
#endif

} // Nam
