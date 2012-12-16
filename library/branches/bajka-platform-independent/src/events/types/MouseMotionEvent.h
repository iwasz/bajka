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

#include "geometry/Point.h"
#include "MouseEvent.h"

namespace Event {
class PointerInsideIndex;

/**
 * Event ruchu myszy.
 * \ingroup Events
 */
class MouseMotionEvent : public MouseEvent {
public:

        MouseMotionEvent () : movement (Geometry::ZERO_POINT) {}
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
        virtual Handling runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return c->onMouseMotionDispatch (static_cast <MouseMotionEvent *> (this), m, v, static_cast <PointerInsideIndex *> (d)); }

        virtual std::string toString () const;

private:

        Geometry::Point movement;
        unsigned int buttons;

};

}

#	endif /* MOUSEMOTIONEVENT_H_ */
