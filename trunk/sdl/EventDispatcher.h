/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <SDL.h>

#include "IEvent.h"
#include "KeyboardEvent.h"
#include "MouseMotionEvent.h"
#include "MouseButtonEvent.h"

namespace Sdl {

class EventDispatcher : public Events::AbstractObservable <Events::KeyboardEvent>,
                        public Events::AbstractObservable <Events::MouseMotionEvent>,
                        public Events::AbstractObservable <Events::MouseButtonEvent> {
public:

        virtual ~EventDispatcher () {}

        void run (SDL_Event *event);

private:

        const Events::KeyboardEvent &updateKeyboardEvent (SDL_Event *event);
        const Events::MouseMotionEvent &updateMouseMotionEvent (SDL_Event *event);
        const Events::MouseButtonEvent &updateMouseButtonEvent (SDL_Event *event);

private:

        // This makes sense only when app is single-threaded.
        Events::KeyboardEvent keyboardEvent;
        Events::MouseMotionEvent mouseMotionEvent;
        Events::MouseButtonEvent mouseButtonEvent;

};

}

#	endif /* EVENTDISPATCHER_H_ */
