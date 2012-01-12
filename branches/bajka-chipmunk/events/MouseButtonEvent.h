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

#include "MouseEvent.h"
#include "Common.h"
#include "Point.h"

namespace Event {

/**
 * Event kliknięcia klawisza myszy.
 * \ingroup Events
 */
class MouseButtonEvent : public MouseEvent {
public:

        MouseButtonEvent () : button (static_cast <MouseButton> (0)) {}
        MouseButtonEvent (MouseButton button, const Geometry::Point &position) :
                MouseEvent (position),
                button (button) {}

        virtual ~MouseButtonEvent () {}

        /**
         * Wciśnięty guzik myszy. Wartość typu Event::MouseButton (należy porównywać
         * ze zdefiniowanymi stałymi).
         */
        MouseButton getButton () const { return button; }
        void setButton (MouseButton button) { this->button = button; }

private:

        MouseButton button;

};

/**
 * Event oznaczający wciśnięcie guzika myszy.
 * \ingroup Events
 */
struct ButtonPressEvent : public MouseButtonEvent {
        virtual ~ButtonPressEvent () {}
        Type getType () const { return  BUTTON_PRESS_EVENT; }
        virtual bool runCallback (Controller::IController *c) { return c->onButtonPress (static_cast <ButtonPressEvent *> (this)); }
};

/**
 * Event oznaczający puszczenie guzika myszy.
 * \ingroup Events
 */
struct ButtonReleaseEvent : public MouseButtonEvent {
        virtual ~ButtonReleaseEvent () {}
        Type getType () const { return  BUTTON_RELEASE_EVENT; }
        virtual bool runCallback (Controller::IController *c) { return c->onButtonRelease (static_cast <ButtonReleaseEvent *> (this)); }
};

}

#	endif /* MOUSEBUTTONEVENT_H_ */
