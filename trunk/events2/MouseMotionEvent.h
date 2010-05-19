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
#include "IEvent.h"
#include "geometry/Point.h"

namespace Event {

class MouseMotionEvent : public IEvent {
public:

        MouseMotionEvent () {}
        MouseMotionEvent (const Geometry::Point &position, const Geometry::Point &movement, MouseButton b) : position (position), movement (movement), button (button) {}
        virtual ~MouseMotionEvent () {}

        MouseButton getButton () const { return button; }
        void setButton (MouseButton button) { this->button = button; }

        const Geometry::Point &getMovement () const { return movement; }
        void setMovement (const Geometry::Point &movement) { this->movement = movement; }

        const Geometry::Point &getPosition () const {  return position; }
        void setPosition (const Geometry::Point &position) { this->position = position; }

        Type getType () const { return MOUSE_MOTION_EVENT; }

private:

        Geometry::Point position;
        Geometry::Point movement;
        MouseButton button;

};

}

#	endif /* MOUSEMOTIONEVENT_H_ */
