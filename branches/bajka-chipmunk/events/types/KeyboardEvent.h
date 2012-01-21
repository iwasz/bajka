/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef KEYBOARDEVENT_H_
#define KEYBOARDEVENT_H_

#include "IEvent.h"
#include "KeyCode.h"

namespace Event {

/**
 * Event związany z klawiaturą.
 * \ingroup Events
 */
class KeyboardEvent : public IEvent {
public:

        virtual ~KeyboardEvent () {}

        KeyCode getKeyCode() const { return keyCode; }
        void setKeyCode(KeyCode keyCode) { this->keyCode = keyCode; }

        KeyMod getKeyMod() const { return keyMod; }
        void setKeyMod(KeyMod keyMod) { this->keyMod = keyMod; }

protected:

        KeyCode keyCode;
        KeyMod keyMod;

};

}

#	endif /* KEYBOARDEVENT_H_ */
