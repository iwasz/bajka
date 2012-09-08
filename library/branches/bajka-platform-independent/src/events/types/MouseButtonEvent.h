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
#include "geometry/Point.h"

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

protected:

        MouseButton button;

};

}

#	endif /* MOUSEBUTTONEVENT_H_ */
