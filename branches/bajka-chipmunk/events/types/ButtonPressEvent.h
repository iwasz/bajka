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
        virtual bool runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, IDispatcher *d) { return c->onButtonPress (static_cast <ButtonPressEvent *> (this), m, v); }
        virtual std::string toString () const;
};

} /* namespace Event */

#	endif /* BUTTONPRESSEVENT_H_ */
