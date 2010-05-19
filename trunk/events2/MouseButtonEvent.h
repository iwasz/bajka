/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MOUSEBUTTONEVENT_H_
#define MOUSEBUTTONEVENT_H_

#include "IEvent.h"
#include "Common.h"
#include "geometry/Point.h"

namespace Event {

class MouseButtonEvent : public IEvent {
public:

        enum Press { DOWN, UP };

        MouseButtonEvent () {}
        MouseButtonEvent (Press type, MouseButton button, const Geometry::Point &position) : press (type), button (button), position (position) {}
        virtual ~MouseButtonEvent () {}

        Press getPress () const { return press; }
        void setPress (Press t) { this->press = t; }

        MouseButton getButton () const { return button; }
        void setButton (MouseButton button) { this->button = button; }

        const Geometry::Point &getPosition () const {  return position; }
        void setPosition (const Geometry::Point &position) { this->position = position; }

        Type getType () const { return MOUSE_BUTTON_EVENT; }

private:

        Press press;
        MouseButton button;
        Geometry::Point position;

};

}

#	endif /* MOUSEBUTTONEVENT_H_ */
