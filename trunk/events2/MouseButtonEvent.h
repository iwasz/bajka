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

#include "IObserver.h"
#include "MouseEvent.h"
#include "Common.h"
#include "geometry/Point.h"

namespace Event {

class MouseButtonEvent : public MouseEvent {
public:

        enum Press { DOWN, UP };

        MouseButtonEvent () {}
        MouseButtonEvent (Press type, MouseButton button, const Geometry::Point &position) : MouseEvent (position), press (type), button (button) {}
        virtual ~MouseButtonEvent () {}

        Press getPress () const { return press; }
        void setPress (Press t) { this->press = t; }

        MouseButton getButton () const { return button; }
        void setButton (MouseButton button) { this->button = button; }

private:

        Press press;
        MouseButton button;

};

/**
 *
 */
struct ButtonPressEvent : public MouseButtonEvent {
        virtual ~ButtonPressEvent () {}
        Type getType () const { return  BUTTON_PRESS_EVENT; }
        // Jesli to zadziała, to wywalić getType.
        virtual void runObserver (IObserver *o) { o->onButtonPress (static_cast <ButtonPressEvent *> (this)); }
};

/**
 *
 */
struct ButtonReleaseEvent : public MouseButtonEvent {
        virtual ~ButtonReleaseEvent () {}
        Type getType () const { return  BUTTON_RELEASE_EVENT; }
        virtual void runObserver (IObserver *o) { o->onButtonRelease (static_cast <ButtonReleaseEvent *> (this)); }
};

}

#	endif /* MOUSEBUTTONEVENT_H_ */
