/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BUTTONRELEASEEVENT_H_
#define BUTTONRELEASEEVENT_H_

#include "MouseButtonEvent.h"

namespace Event {

/**
 * Event oznaczający puszczenie guzika myszy.
 * \ingroup Events
 */
struct ButtonReleaseEvent : public MouseButtonEvent {
        virtual ~ButtonReleaseEvent () {}
        Type getType () const { return  BUTTON_RELEASE_EVENT; }
        virtual Handling runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return c->onButtonRelease (static_cast <ButtonReleaseEvent *> (this), m, v); }
        virtual std::string toString () const;
};

} /* namespace Event */

#	endif /* BUTTONRELEASEEVENT_H_ */
