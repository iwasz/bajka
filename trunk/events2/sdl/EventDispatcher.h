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
#include <Reflection.h>

#include "IEvent.h"
#include "KeyboardEvent.h"
#include "MouseMotionEvent.h"
#include "MouseButtonEvent.h"
#include "IObserver.h"
#include "IDispatcher.h"

namespace Sdl {

class EventDispatcher : public Event::IDispatcher {
public:
        __c (void)

        EventDispatcher () : observer (NULL) {}
        virtual ~EventDispatcher () {}

        void run ();
        void translate (SDL_Event *event);

/*--------------------------------------------------------------------------*/

        Event::IObserver *getObserver () const { return observer; }
        _m (setObserver) void setObserver (Event::IObserver *o) { observer = o; }

private:

        const Event::KeyboardEvent &updateKeyboardEvent (SDL_Event *event);
        const Event::MouseMotionEvent &updateMouseMotionEvent (SDL_Event *event);
        const Event::MouseButtonEvent &updateMouseButtonEvent (SDL_Event *event);

private:

        // This makes sense only when app is single-threaded.
        Event::KeyboardEvent keyboardEvent;
        Event::MouseMotionEvent mouseMotionEvent;
        Event::MouseButtonEvent mouseButtonEvent;
        Event::IObserver *observer;

        _e (EventDispatcher)
};

}

#	endif /* EVENTDISPATCHER_H_ */
