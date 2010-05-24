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

        if (observer) {
                observer->onEvent (&timerEvent);
        }
}

}
