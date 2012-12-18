/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MOUSEMOTIONEVENT_H_
#define MOUSEMOTIONEVENT_H_

#include "geometry/Point.h"
#include "MotionEvent.h"

namespace Event {
class PointerInsideIndex;

/**
 * Event ruchu myszy.
 * \ingroup Events
 */
class MotionMoveEvent : public MotionEvent {
public:

        virtual ~MotionMoveEvent () {}

        Type getType () const { return MOTION_MOVE_EVENT; }
        virtual Handling runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return c->onMotionMoveDispatch (static_cast <MotionMoveEvent *> (this), m, v, static_cast <PointerInsideIndex *> (d)); }
        virtual std::string toString () const;
};

}

#	endif /* MOUSEMOTIONEVENT_H_ */
