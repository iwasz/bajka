/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_SDL
#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <SDL.h>
#include "ReflectionMacros.h"
#include "AbstractEventDispatcher.h"
#include "App.h"
#include "types/Types.h"

namespace Event {

/**
 * Generuje eventy używając do tego SDL.
 * \ingroup Events
 */
class EventDispatcher : public AbstractEventDispatcher {
public:
        b__ ("AbstractEventDispatcher")
        C_ (void)

        virtual ~EventDispatcher () {}

        void pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex);
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

        E_ (EventDispatcher)
};

}

#endif /* EVENTDISPATCHER_H_ */
#endif
