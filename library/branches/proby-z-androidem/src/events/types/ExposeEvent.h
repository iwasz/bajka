/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EXPOSEEVENT_H_
#define BAJKA_EXPOSEEVENT_H_

#include "IEvent.h"

namespace Event {

class ExposeEvent : public IEvent {
public:
        virtual ~ExposeEvent () {}

        Type getType () const { return EXPOSE_EVENT; }
        bool runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return c->onExpose (static_cast <ExposeEvent *> (this), m, v); }

        std::string toString () const { return "ExposeEvent ()"; }
};

} /* namespace Event */

#	endif /* EXPOSEEVENT_H_ */
