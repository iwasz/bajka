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

namespace Events {

class MouseButtonEvent : public IEvent {
public:

        enum Type { DOWN, UP };

        MouseButtonEvent () {}
        MouseButtonEvent (Type type, MouseButton button, const Geometry::Point &position) : type (type), button (button), position (position) {}
        virtual ~MouseButtonEvent () {}

        Type getType () const { return type; }
        void setType (Type type) { this->type = type; }

        MouseButton getButton () const { return button; }
        void setButton (MouseButton button) { this->button = button; }

        const Geometry::Point &getPosition () const {  return position; }
        void setPosition (const Geometry::Point &position) { this->position = position; }

private:

        Type type;
        MouseButton button;
        Geometry::Point position;

};

}

#	endif /* MOUSEBUTTONEVENT_H_ */
