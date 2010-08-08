/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TIMEREVENT_H_
#define TIMEREVENT_H_

#include "IEvent.h"
#include "IObserver.h"

namespace Event {

/**
 * Event zegarowy.
 * \ingroup Events
 */
class TimerEvent : public AbstractEvent {
public:

        TimerEvent () : ticks (0) {}
        virtual ~TimerEvent () {}

        unsigned int getTicks () const { return ticks; }
        void setTicks (unsigned int ticks) { this->ticks = ticks; }

        Type getType () const { return TIMER_EVENT; }
        virtual void runObserver (IObserver *o) { o->onTimer (static_cast <TimerEvent *> (this)); }

private:

        unsigned int ticks;
};

}

#	endif /* TIMEREVENT_H_ */
