/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ACTIVEEVENT_H_
#define BAJKA_ACTIVEEVENT_H_

#include "IEvent.h"

namespace Event {

enum ActiveState {
        MOUSE = 0x01,
        KEYBOARD = 0x02,
        WINDOW = 0x04
};

/**
 *
 */
class ActiveEvent : public IEvent {
public:

        virtual ~ActiveEvent () {}

        ActiveState getState () const { return state; }
        void setState (ActiveState state) { this->state = state; }

        bool getActive () const { return active; }
        void setActive (bool active) { this->active = active; }

        std::string toString () const;
        Type getType () const { return ACTIVE_EVENT; }
        bool runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, IDispatcher *d) { return c->onActive (static_cast <ActiveEvent *> (this), m, v); }

private:

        bool active;
        ActiveState state;

};

} /* namespace Event */

#	endif /* ACTIVEEVENT_H_ */
