/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 19, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <algorithm>
#include <SDL.h>

#include "TimerDispatcher.h"

namespace Sdl {

void TimerDispatcher::run ()
{
        unsigned int now = SDL_GetTicks ();

        if (now - prevTime < tickInterval) {
                return;
        }

        prevTime = now;
        timerEvent.setTicks (now);

//        if (observer) {
//                observer->onEvent (&timerEvent);
//        }

        for (Event::ObserverVector::iterator i = observers.begin (); i != observers.end (); ++i) {
                (*i)->onEvent (&timerEvent);
        }
}

}
