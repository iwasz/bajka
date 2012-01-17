/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef KEYDOWNEVENT_H_
#define KEYDOWNEVENT_H_

#include "KeyboardEvent.h"
#include <string>

namespace Event {

/**
 * Event naciśnięcie klawisza na klawiaturze.
 * \ingroup Events
 */
struct KeyDownEvent : public KeyboardEvent {
        virtual ~KeyDownEvent () {}
        Type getType () const { return  KEY_DOWN_EVENT; }
        virtual bool runCallback (Controller::IController *c) { return c->onKeyDown (static_cast <KeyDownEvent *> (this)); }
        virtual std::string toString () const;
};

} /* namespace Event */

#	endif /* KEYDOWNEVENT_H_ */
