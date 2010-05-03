/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 19, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TIMERDISPATCHER_H_
#define TIMERDISPATCHER_H_

#include "TimerEvent.h"

namespace Sdl {

class TimerDispatcher : public Events::AbstractObservable <Events::TimerEvent> {
public:

        TimerDispatcher () : tickInterval (30), prevTime (0) {}

        void run ();

        int getTickInterval () const { return tickInterval; }
        void setTickInterval (int tickInterval) { this->tickInterval = tickInterval; }

private:

        int tickInterval;
        unsigned int prevTime;
        Events::TimerEvent timerEvent;

};

}

#	endif /* TIMERDISPATCHER_H_ */
