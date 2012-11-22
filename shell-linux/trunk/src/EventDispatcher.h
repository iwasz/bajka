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

        /**
         * Pobiera kolejne eventy z systemu i przekazuje je do dispatch.
         */
        bool pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex, View::GLContext const *ctx);

        void reset ();

private:

        Event::IEvent *translate (SDL_Event *event, View::GLContext const *ctx);
        Event::MouseButton translateMouseButton (SDL_Event *event);

        Event::KeyboardEvent *updateKeyboardUpEvent (SDL_Event *event);
        Event::KeyboardEvent *updateKeyboardDownEvent (SDL_Event *event);
        Event::MouseMotionEvent *updateMouseMotionEvent (SDL_Event *event, View::GLContext const *ctx);
        Event::MouseButtonEvent *updateMouseButtonEvent (SDL_Event *event, View::GLContext const *ctx);
        Event::MouseButtonEvent *updateMouseButtonEventImpl (Event::MouseButtonEvent *output, SDL_Event *event, View::GLContext const *ctx);
        Event::ActiveEvent *updateActiveEvent (SDL_Event *event);
        Event::ResizeEvent *updateResizeEvent (SDL_Event *event);

private:

        // This makes sense only when app is single-threaded.
        Event::MouseMotionEvent mouseMotionEvent;
        Event::KeyUpEvent keyUpEvent;
        Event::KeyDownEvent keyDownEvent;
        Event::ButtonPressEvent buttonPressEvent;
        Event::ButtonReleaseEvent buttonReleaseEvent;
        Event::QuitEvent quitEvent;
        Event::ResizeEvent resizeEvent;
        Event::ActiveEvent activeEvent;
        Event::ExposeEvent exposeEvent;
};

#endif /* EVENTDISPATCHER_H_ */
