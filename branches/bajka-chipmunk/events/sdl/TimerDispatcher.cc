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
using namespace Event;

//void TimerDispatcher::addObserver (Ptr <IObserver> o)
//{
//        observers.push_back (o);
//}
//
///****************************************************************************/
//
//void TimerDispatcher::removeObserver (Ptr <IObserver> o)
//{
//        observers.erase (std::remove (observers.begin (), observers.end (), o), observers.end ());
//}

/****************************************************************************/

void TimerDispatcher::run (Model::IModel *m, ModelIndex const &modeliIndex)
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
