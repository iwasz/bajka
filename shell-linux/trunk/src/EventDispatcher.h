/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <SDL.h>
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

/**
 * Generuje eventy używając do tego SDL.
 * \ingroup Events
 */
class EventDispatcher : public Event::AbstractEventDispatcher {
public:
        virtual ~EventDispatcher () {}

        void reset ();
        void init (void *userData);
        bool process (void *systemEvent,
                      Model::IModel *model,
                      Event::EventIndex const &modeliIndex,
                      Event::PointerInsideIndex *pointerInsideIndex,
                      View::GLContext const *ctx);
private:

        Event::IEvent *translate (SDL_Event *event, View::GLContext const *ctx);
        Event::KeyboardEvent *updateKeyboardUpEvent (SDL_Event *event);
        Event::KeyboardEvent *updateKeyboardDownEvent (SDL_Event *event);
        Event::MotionEvent *updateMotionEvent (SDL_Event *event, View::GLContext const *ctx);
        Event::MotionEvent *updateMouseButtonEvent (Event::MotionEvent *output, SDL_Event *event, View::GLContext const *ctx);

private:

        // This makes sense only when app is single-threaded.
        Event::MotionMoveEvent motionMoveEvent;
        Event::MotionDownEvent motionDownEvent;
        Event::MotionUpEvent motionUpEvent;
        Event::KeyUpEvent keyUpEvent;
        Event::KeyDownEvent keyDownEvent;
        Event::QuitEvent quitEvent;
};

#endif /* EVENTDISPATCHER_H_ */
