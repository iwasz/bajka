/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BUTTONRELEASEEVENT_H_
#define BUTTONRELEASEEVENT_H_

#include "MotionEvent.h"

namespace Event {

/**
 * Event oznaczający puszczenie guzika myszy.
 * \ingroup Events
 */
struct MotionUpEvent : public MotionEvent {
        virtual ~MotionUpEvent () {}
        Type getType () const { return  MOTION_UP_EVENT; }
        virtual Handling runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return c->onMotionUp (static_cast <MotionUpEvent *> (this), m, v); }
        virtual std::string toString () const;
};

} /* namespace Event */

#	endif /* BUTTONRELEASEEVENT_H_ */
