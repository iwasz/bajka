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
#include "Point.h"

namespace Events {

class MouseMotionEvent : public IEvent {
public:

        MouseMotionEvent () {}
        MouseMotionEvent (const Model::Point &position, const Model::Point &movement, MouseButton b) : position (position), movement (movement), button (button) {}
        virtual ~MouseMotionEvent () {}

        MouseButton getButton () const { return button; }
        void setButton (MouseButton button) { this->button = button; }

        const Model::Point &getMovement () const { return movement; }
        void setMovement (const Model::Point &movement) { this->movement = movement; }

        const Model::Point &getPosition () const {  return position; }
        void setPosition (const Model::Point &position) { this->position = position; }

private:

        Model::Point position;
        Model::Point movement;
        MouseButton button;

};

}

#	endif /* MOUSEMOTIONEVENT_H_ */
