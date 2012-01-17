/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BUTTONRELEASEEVENT_H_
#define BUTTONRELEASEEVENT_H_

#include "types/MouseButtonEvent.h"

namespace Event {

/**
 * Event oznaczający puszczenie guzika myszy.
 * \ingroup Events
 */
struct ButtonReleaseEvent : public MouseButtonEvent {
        virtual ~ButtonReleaseEvent () {}
        Type getType () const { return  BUTTON_RELEASE_EVENT; }
        virtual bool runCallback (Controller::IController *c) { return c->onButtonRelease (static_cast <ButtonReleaseEvent *> (this)); }
        virtual std::string toString () const;
};

} /* namespace Event */

#	endif /* BUTTONRELEASEEVENT_H_ */
