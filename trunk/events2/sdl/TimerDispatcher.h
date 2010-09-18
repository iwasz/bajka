/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TIMERDISPATCHER_H_
#define TIMERDISPATCHER_H_

#include <Reflection.h>

#include "TimerEvent.h"
#include "IObserver.h"
#include "IDispatcher.h"

namespace Sdl {

/**
 * Generuje eventy zegarowe używając do tego timerów SDL.
 * \ingroup Events
 */
class TimerDispatcher : public Event::IDispatcher {
public:
        __c (void)

        TimerDispatcher () : tickInterval (30), prevTime (0)/*, observer (NULL)*/ {}

        void run ();

/*--------------------------------------------------------------------------*/

//        Event::IObserver *getObserver () const { return observer; }
//        _m (setObserver) void setObserver (Event::IObserver *o) { observer = o; }

        _m (setObservers) void setObservers (Event::ObserverVector const &o) { observers = o; }
        Event::ObserverVector const &getObservers () const { return observers; }

        int getTickInterval () const { return tickInterval; }
        _m (setTickInterval) void setTickInterval (int tickInterval) { this->tickInterval = tickInterval; }

private:

        int tickInterval;
        unsigned int prevTime;
        Event::TimerEvent timerEvent;
//        Event::IObserver *observer;
        Event::ObserverVector observers;

        _e (TimerDispatcher)
};

}

#	endif /* TIMERDISPATCHER_H_ */
