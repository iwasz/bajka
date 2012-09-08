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
#include "events/types/Types.h"

namespace Model {
class IModel;
}

namespace Event {
class PointerInsideIndex;
class EventIndex;
}

/**
 * Generuje eventy używając do tego SDL.
 * \ingroup Events
 */
class EventDispatcher {
public:
        virtual ~EventDispatcher () {}

        /**
         * Pobiera kolejne eventy z systemu i przekazuje je do dispatch.
         */
        bool pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex);

        /**
         * Zwraca true, kiedy event został obsłużony przez grę i nie powinien zostać przekazany do
         * systemu. Ma to znaczenie w androidzie, gdzie aplikacja i system współdzielą eventy.
         */
        virtual bool dispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex, SDL_Event *event);

        void reset ();

private:

        Event::IEvent *translate (SDL_Event *event);

        Event::KeyboardEvent *updateKeyboardUpEvent (SDL_Event *event);
        Event::KeyboardEvent *updateKeyboardDownEvent (SDL_Event *event);
        Event::MouseMotionEvent *updateMouseMotionEvent (SDL_Event *event);
        Event::MouseButtonEvent *updateMouseButtonEvent (SDL_Event *event);
        Event::MouseButtonEvent *updateMouseButtonEventImpl (Event::MouseButtonEvent *output, SDL_Event *event);
        Event::ActiveEvent *updateActiveEvent (SDL_Event *event);
        Event::ResizeEvent *updateResizeEvent (SDL_Event *event);

        Event::MouseButton translateMouseButton (SDL_Event *event);
        bool dispatchEventBackwards (Model::IModel *m, Event::IEvent *e, Event::PointerInsideIndex *pointerInsideIndex);

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
