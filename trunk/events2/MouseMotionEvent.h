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

#include "Common.h"
#include "MouseEvent.h"
#include "geometry/Point.h"
#include "IObserver.h"

namespace Event {

/**
 * Event ruchu myszy.
 * \ingroup Events
 */
class MouseMotionEvent : public MouseEvent {
public:

        MouseMotionEvent () {}
        MouseMotionEvent (const Geometry::Point &position, const Geometry::Point &movement, MouseButton b) : MouseEvent (position), movement (movement), button (button) {}
        virtual ~MouseMotionEvent () {}

        MouseButton getButton () const { return button; }
        void setButton (MouseButton button) { this->button = button; }

        const Geometry::Point &getMovement () const { return movement; }
        void setMovement (const Geometry::Point &movement) { this->movement = movement; }

        Type getType () const { return MOUSE_MOTION_EVENT; }
        virtual void runObserver (IObserver *o) { o->onMouseMotion (static_cast <MouseMotionEvent *> (this)); }

private:

        Geometry::Point movement;
        MouseButton button;

};

}

#	endif /* MOUSEMOTIONEVENT_H_ */
