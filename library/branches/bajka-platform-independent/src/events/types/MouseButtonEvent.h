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

#include "MotionEvent.h"
#include "geometry/Point.h"

namespace Event {

/**
 * Event kliknięcia klawisza myszy.
 * \ingroup Events
 */
class MouseButtonEvent : public MotionEvent {
public:

        MouseButtonEvent () : button (static_cast <MotionButton> (0)) {}
        MouseButtonEvent (MotionButton button, const Geometry::Point &position) :
                MotionEvent (),
                button (button) {}

        virtual ~MouseButtonEvent () {}

        /**
         * Wciśnięty guzik myszy. Wartość typu Event::MouseButton (należy porównywać
         * ze zdefiniowanymi stałymi).
         */
        MotionButton getButton () const { return button; }
        void setButton (MotionButton button) { this->button = button; }

protected:

        MotionButton button;

};

}

#	endif /* MOUSEBUTTONEVENT_H_ */
