/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHELL_EVENTDISPATCHER_H_
#define SHELL_EVENTDISPATCHER_H_

#include <android/input.h>
#include <android/sensor.h>
#include <events/types/Types.h>
#include <events/AbstractEventDispatcher.h>

namespace Model {
class IModel;
}

namespace Event {
class PointerInsideIndex;
class EventIndex;
}

namespace View {
class GLContext;
}

struct android_app;

/**
 * Generuje eventy używając do tego SDL.
 * \ingroup Events
 */
class EventDispatcher : public Event::AbstractEventDispatcher {
public:
        EventDispatcher () : app (NULL), sensorManager (NULL), accelerometerSensor (NULL), sensorEventQueue (NULL) {}
        virtual ~EventDispatcher () {}

        void reset ();
        void init (void *userData);
        bool process (void *systemEvent,
                      Model::IModel *model,
                      Event::EventIndex const &modeliIndex,
                      Event::PointerInsideIndex *pointerInsideIndex,
                      View::GLContext const *ctx);

private:

        Event::IEvent *translate (void *systemEvent, View::GLContext const *ctx);

        Event::KeyboardEvent *updateKeyboardUpEvent (AInputEvent *event);
        Event::KeyboardEvent *updateKeyboardDownEvent (AInputEvent *event);
        Event::MotionEvent *updateMotionEvent (Event::MotionEvent *output, AInputEvent const *event, View::GLContext const *ctx);
        Event::ResizeEvent *updateResizeEvent (AInputEvent *event);

private:

        Event::MotionMoveEvent motionMoveEvent;
        Event::MotionDownEvent motionDownEvent;
        Event::MotionUpEvent motionUpEvent;

        Event::KeyDownEvent keyDownEvent;
        Event::KeyUpEvent keyUpEvent;

        Event::QuitEvent quitEvent;
        Event::ResizeEvent resizeEvent;

        android_app *app;
        ASensorManager *sensorManager;
        const ASensor *accelerometerSensor;
        ASensorEventQueue *sensorEventQueue;
};

#endif /* EVENTDISPATCHER_H_ */
