/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 19, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_SDL
#include <iostream>
#include <algorithm>
#include <SDL.h>

#include "TimerDispatcher.h"

namespace Event {

void TimerDispatcher::run (Model::IModel *m, EventIndex const &modeliIndex, PointerInsideIndex *pointerInsideIndex)
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

//        for (Event::ObserverVector::iterator i = observers.begin (); i != observers.end (); ++i) {
//                (*i)->onEvent (&timerEvent);
//        }
}

}

#endif
