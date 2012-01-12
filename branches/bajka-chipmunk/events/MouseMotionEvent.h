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

#include "Point.h"
#include "Common.h"
#include "MouseEvent.h"

namespace Event {

/**
 * Event ruchu myszy.
 * \ingroup Events
 */
class MouseMotionEvent : public MouseEvent {
public:

        MouseMotionEvent () {}
        MouseMotionEvent (const Geometry::Point &position, const Geometry::Point &movement, unsigned int b) :
                MouseEvent (position),
                movement (movement),
                buttons (b) {}

        virtual ~MouseMotionEvent () {}

        /**
         * Maska bitowa aktualnie wciśniętych guzików. Należy ją porównywać
         * ze stałymi z enum Event::MouseButton.
         */
        unsigned int getButtons () const { return buttons; }
        void setButtons (unsigned int button) { this->buttons = button; }

        /**
         * Relatywny ruch kursora we współrzędnych device-coordinates. Jest to
         * różnica między aktualną a poprzednią pozycją kursora.
         */
        const Geometry::Point &getMovement () const { return movement; }
        void setMovement (const Geometry::Point &movement) { this->movement = movement; }

        Type getType () const { return MOUSE_MOTION_EVENT; }
        virtual bool runCallback (Controller::IController *c) { return c->onMouseMotion (static_cast <MouseMotionEvent *> (this)); }

private:

        Geometry::Point movement;
        unsigned int buttons;

};

}

#	endif /* MOUSEMOTIONEVENT_H_ */
