/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "EventDispatcher.h"
#include <events/PointerInsideIndex.h>
#include <events/EventIdex.h>
#include <events/types/IEvent.h>
#include <model/IGroup.h>
#include <Platform.h>
#include <util/IShell.h>
#include <util/Config.h>
#include <view/openGl/GLContext.h>
#include <android_native_app_glue.h>

namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace G = Geometry;
using namespace Event;

/****************************************************************************/

bool EventDispatcher::pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex, View::GLContext const *ctx)
{
        int ident;
        int events;
        struct android_poll_source* source;
        bool ret = false;

        while ((ident = ALooper_pollAll (0, NULL, &events, (void**)&source)) >= 0) {

            if (source != NULL) {
                source->process (app, source);
            }

            if (ident == LOOPER_ID_USER) {
                if (accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents (sensorEventQueue, &event, 1) > 0) {
                        // LOGI("accelerometer: x=%f y=%f z=%f", event.acceleration.x, event.acceleration.y, event.acceleration.z);
                    }
                }
            }

            if (app->destroyRequested != 0) {
                shell ()->quit ();
                return true; //?
            }
        }

        return ret;
}

/****************************************************************************/

Event::IEvent *EventDispatcher::translate (AInputEvent *event, View::GLContext const *ctx)
{
        int32_t eventType = AInputEvent_getType (event);

        if (eventType == AINPUT_EVENT_TYPE_MOTION) {
                return updateMouseMotionEvent (event, ctx);
        }
        else if (eventType == AINPUT_EVENT_TYPE_KEY) {

        }


//        switch (event->type) {
//        case SDL_MOUSEMOTION:
//                return updateMouseMotionEvent (event, ctx);
//
//        case SDL_MOUSEBUTTONDOWN:
//        case SDL_MOUSEBUTTONUP:
//                return updateMouseButtonEvent (event, ctx);
//
//        case SDL_KEYDOWN:
//                return updateKeyboardDownEvent (event);
//
//        case SDL_KEYUP:
//                return updateKeyboardUpEvent (event);
//
//        case SDL_QUIT:
//                return &quitEvent;
//
//        case SDL_ACTIVEEVENT:
//                return updateActiveEvent (event);
//
//        case SDL_VIDEORESIZE:
//                return updateResizeEvent (event);
//
//        case SDL_VIDEOEXPOSE:
//                return &exposeEvent;
//
//        default:
//                break;
//        }

        return NULL;
}

/****************************************************************************/

KeyboardEvent *EventDispatcher::updateKeyboardUpEvent (AInputEvent *event)
{
//        keyUpEvent.setKeyCode (static_cast <KeyCode> (event->key.keysym.sym));
//        keyUpEvent.setKeyMod (static_cast <KeyMod> (event->key.keysym.mod));
        return &keyUpEvent;
}

/****************************************************************************/

KeyboardEvent *EventDispatcher::updateKeyboardDownEvent (AInputEvent *event)
{
//        keyDownEvent.setKeyCode (static_cast <KeyCode> (event->key.keysym.sym));
//        keyDownEvent.setKeyMod (static_cast <KeyMod> (event->key.keysym.mod));
        return &keyDownEvent;
}

/****************************************************************************/

MouseMotionEvent *EventDispatcher::updateMouseMotionEvent (AInputEvent *event, View::GLContext const *ctx)
{
//        mouseMotionEvent.setButtons ((unsigned int)event->motion.state);
        mouseMotionEvent.setButtons (0);

        float x = AMotionEvent_getX (event, 0);
        float y = AMotionEvent_getY (event, 0);

        G::Point p;
        ctx->mouseToDisplay (x, y, &p.x, &p.y);
        mouseMotionEvent.setPosition (p);

#if 1
        printlog ("Motion event %f, %f", p.x, p.y);
#endif
#if 0
        std::cerr << event->motion.xrel << ", " << event->motion.yrel << std::endl;
#endif

        // ?
//        mouseMotionEvent.setMovement (G::makePoint (event->motion.xrel, event->motion.yrel));

        return &mouseMotionEvent;
}

/****************************************************************************/

MouseButtonEvent *EventDispatcher::updateMouseButtonEvent (AInputEvent *event, View::GLContext const *ctx)
{
//        return (event->button.type == SDL_MOUSEBUTTONDOWN) ?
//                        (updateMouseButtonEventImpl (&buttonPressEvent, event, ctx)) :
//                        (updateMouseButtonEventImpl (&buttonReleaseEvent, event, ctx));
        return updateMouseButtonEventImpl (&buttonPressEvent, event, ctx);
}

/*--------------------------------------------------------------------------*/

MouseButtonEvent *EventDispatcher::updateMouseButtonEventImpl (MouseButtonEvent *output, AInputEvent *event, View::GLContext const *ctx)
{
//        output->setButton (translateMouseButton (event));
        mouseMotionEvent.setButtons (0);

        float x = AMotionEvent_getX (event, 0);
        float y = AMotionEvent_getY (event, 0);

        G::Point p;
        ctx->mouseToDisplay (x, y, &p.x, &p.y);
        mouseMotionEvent.setPosition (p);
}

/*--------------------------------------------------------------------------*/

MouseButton EventDispatcher::translateMouseButton (AInputEvent *event)
{
//        switch (event->button.button) {
//        case SDL_BUTTON_MIDDLE:
//                return CENTER;
//
//        case SDL_BUTTON_RIGHT:
//                return RIGHT;
//
//        case 4:
//                return BUTTON4;
//
//        case 5:
//                return BUTTON5;
//
//        case 6:
//                return BUTTON6;
//
//        case 7:
//                return BUTTON7;
//
//        case 8:
//                return BUTTON8;
//
//        default:
//        case SDL_BUTTON_LEFT:
//                return LEFT;
//        }
}

/****************************************************************************/

Event::ActiveEvent *EventDispatcher::updateActiveEvent (AInputEvent *event)
{
//        activeEvent.setActive (event->active.gain);
//        activeEvent.setState (static_cast <ActiveState> (event->active.state));
//        return &activeEvent;
}

/****************************************************************************/

Event::ResizeEvent *EventDispatcher::updateResizeEvent (AInputEvent *event)
{
//        resizeEvent.setWidth (event->resize.w);
//        resizeEvent.setHeight (event->resize.h);
//        return &resizeEvent;
}

/****************************************************************************/

void EventDispatcher::reset ()
{
//        // Discard all pending events
//        SDL_Event event;
//
//        while (SDL_PollEvent (&event) > 0)
//                ;
}

/****************************************************************************/

void EventDispatcher::init (void *userData)
{
        app = static_cast <android_app *> (userData);

        // Prepare to monitor accelerometer
        sensorManager = ASensorManager_getInstance ();
        accelerometerSensor = ASensorManager_getDefaultSensor (sensorManager, ASENSOR_TYPE_ACCELEROMETER);
        sensorEventQueue = ASensorManager_createEventQueue (sensorManager, app->looper, LOOPER_ID_USER, NULL, NULL);
}
