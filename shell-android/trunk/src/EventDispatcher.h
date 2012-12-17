/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

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
        Event::MotionPointer translateMouseButton (AInputEvent *event);

        Event::KeyboardEvent *updateKeyboardUpEvent (AInputEvent *event);
        Event::KeyboardEvent *updateKeyboardDownEvent (AInputEvent *event);
        Event::MotionMoveEvent *updateMouseMotionEvent (AInputEvent *event, View::GLContext const *ctx);
        Event::MotionEvent *updateMouseButtonEventImpl (Event::MotionEvent *output, AInputEvent *event, View::GLContext const *ctx);
        Event::ResizeEvent *updateResizeEvent (AInputEvent *event);

private:

        Event::MotionMoveEvent mouseMotionEvent;
        Event::MotionDownEvent buttonPressEvent;
        Event::MotionUpEvent buttonReleaseEvent;

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
