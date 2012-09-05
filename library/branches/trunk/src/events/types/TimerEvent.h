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
#include <string>

namespace Event {

/**
 * Event zegarowy.
 * \ingroup Events
 */
class TimerEvent : public IEvent {
public:

        TimerEvent () : ticks (0) {}
        virtual ~TimerEvent () {}

        unsigned int getTicks () const { return ticks; }
        void setTicks (unsigned int ticks) { this->ticks = ticks; }

        Type getType () const { return TIMER_EVENT; }
        virtual bool runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return c->onTimer (static_cast <TimerEvent *> (this), m, v); }

        virtual std::string toString () const;

private:

        unsigned int ticks;
};

}

#	endif /* TIMEREVENT_H_ */
