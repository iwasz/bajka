/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BUTTONPRESSEVENT_H_
#define BUTTONPRESSEVENT_H_

#include "MotionEvent.h"

namespace Event {

/**
 * Event oznaczający wciśnięcie guzika myszy.
 * \ingroup Events
 */
struct MotionDownEvent : public MotionEvent {
        virtual ~MotionDownEvent () {}
        Type getType () const { return  MOTION_DOWN_EVENT; }
        virtual Handling runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return c->onMotionDown (static_cast <MotionDownEvent *> (this), m, v); }
        virtual std::string toString () const;
};

} /* namespace Event */

#	endif /* BUTTONPRESSEVENT_H_ */
