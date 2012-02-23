/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef KEYUPEVENT_H_
#define KEYUPEVENT_H_

#include "KeyboardEvent.h"
#include <string>

namespace Event {

/**
 * Event zwolnienie klawisza na klawiaturze.
 * \ingroup Events
 */
struct KeyUpEvent : public KeyboardEvent {
        virtual ~KeyUpEvent () {}
        Type getType () const { return  KEY_UP_EVENT; }
        virtual bool runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, IDispatcher *d) { return c->onKeyUp (static_cast <KeyUpEvent *> (this), m, v); }
        virtual std::string toString () const;
};

} /* namespace Event */

#	endif /* KEYUPEVENT_H_ */
