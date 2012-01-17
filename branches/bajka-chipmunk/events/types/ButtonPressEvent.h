/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BUTTONPRESSEVENT_H_
#define BUTTONPRESSEVENT_H_

#include "MouseButtonEvent.h"

namespace Event {

/**
 * Event oznaczający wciśnięcie guzika myszy.
 * \ingroup Events
 */
struct ButtonPressEvent : public MouseButtonEvent {
        virtual ~ButtonPressEvent () {}
        Type getType () const { return  BUTTON_PRESS_EVENT; }
        virtual bool runCallback (Controller::IController *c) { return c->onButtonPress (static_cast <ButtonPressEvent *> (this)); }
        virtual std::string toString () const;
};

} /* namespace Event */

#	endif /* BUTTONPRESSEVENT_H_ */
