/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 20, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TIMEREVENT_H_
#define TIMEREVENT_H_

#include "IEvent.h"

namespace Events {

class TimerEvent : public IEvent {
public:

        TimerEvent () : ticks (0) {}
        virtual ~TimerEvent () {}

        unsigned int getTicks () const { return ticks; }
        void setTicks (unsigned int ticks) { this->ticks = ticks; }

private:

        unsigned int ticks;
};

}

#	endif /* TIMEREVENT_H_ */
