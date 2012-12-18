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
#include <util/Config.h>
#include <view/openGl/GLContext.h>
#include <android_native_app_glue.h>

namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace G = Geometry;
using namespace Event;

/*
 * Właściwości MotionEventa na które bedę reagować :
 * - Action - AMOTION_EVENT_ACTION_DOWN, AMOTION_EVENT_ACTION_UP etc.
 * - AMotionEvent_getMetaState - meta klawisze (alt, shift, ctrl etc) naciśięte podczas tego eventu.
 * - liczba pointerów (lub liczba naciśniętych jednocześnie guzików myszy).
 * - pointers - gdy mysza, to powie które guzki naciśnięte. Gdy pointery, indeksy pointerów.
 * - per pointer:
 * -  x, y - bezwzględna pozycja.
 * -  offsetX, offsetY
 * -  pressure
 * -  size
 */

bool EventDispatcher::process (void *systemEvent,
                               Model::IModel *model,
                               Event::EventIndex const &modeliIndex,
                               Event::PointerInsideIndex *pointerInsideIndex,
                               View::GLContext const *ctx)
{
        Event::IEvent *e = translate (systemEvent, ctx);
        return dispatch (model, modeliIndex, pointerInsideIndex, e);
}

/****************************************************************************/

Event::IEvent *EventDispatcher::translate (void *systemEvent, View::GLContext const *ctx)
{
        AInputEvent *event = static_cast <AInputEvent *> (systemEvent);
        int32_t eventType = AInputEvent_getType (event);

        if (eventType == AINPUT_EVENT_TYPE_MOTION) {

                int32_t i = AMotionEvent_getAction (event);
                unsigned char eventAction = AMOTION_EVENT_ACTION_MASK & i;
//                unsigned char pointerIndex = AMOTION_EVENT_ACTION_POINTER_INDEX_MASK & i;

                switch (eventAction) {
                case AMOTION_EVENT_ACTION_DOWN:
                case AMOTION_EVENT_ACTION_POINTER_DOWN:
                        return updateMotionEvent (&motionDownEvent, event, ctx);

                case AMOTION_EVENT_ACTION_UP:
                case AMOTION_EVENT_ACTION_POINTER_UP:
                        return updateMotionEvent (&motionUpEvent, event, ctx);

                case AMOTION_EVENT_ACTION_MOVE:
                        return updateMotionEvent (&motionMoveEvent, event, ctx);

                default:
                        break;
                }

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

MotionEvent *EventDispatcher::updateMotionEvent (Event::MotionEvent *output, AInputEvent const *event, View::GLContext const *ctx)
{
        size_t pcnt = AMotionEvent_getPointerCount (event);
        output->setPointerCount (pcnt);

        int32_t src = AInputEvent_getSource (event);

        if (src == AINPUT_SOURCE_TOUCHSCREEN) {
                output->setSource (TOUCH);
        }
        else if (src == AINPUT_SOURCE_MOUSE) {
                output->setSource (MOUSE);
        }
        else {
                output->setSource (OTHER);
        }

        // output->setMetaState (); TODO

        for (size_t i = 0; i < pcnt; ++i) {

                float x = AMotionEvent_getX (event, i);
                float y = AMotionEvent_getY (event, i);

                MotionPointer &pointer = output->getPointer (i);
                G::Point &p = pointer.position;
                ctx->mouseToDisplay (x, y, &p.x, &p.y);

                pointer.id = AMotionEvent_getPointerId (event, i);
                pointer.pressure = AMotionEvent_getPressure (event, i);
                pointer.size = AMotionEvent_getSize (event, i);
                // pointer.movement = ? TODO
        }

#if 0
        printlog (output->toString ().c_str ());
#endif
        return output;
}

/****************************************************************************/

Event::ResizeEvent *EventDispatcher::updateResizeEvent (AInputEvent *event)
{
//        resizeEvent.setWidth (event->resize.w);
//        resizeEvent.setHeight (event->resize.h);
        return &resizeEvent;
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
