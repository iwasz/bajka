/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MOUSE_BAJKA_EVENT_H_
#define MOUSE_BAJKA_EVENT_H_

#include "Common.h"
#include "IEvent.h"
#include "geometry/Point.h"
#include "IObserver.h"

namespace Event {

class MouseEvent : public AbstractEvent {
public:

        MouseEvent () {}
        MouseEvent (const Geometry::Point &position) : position (position) {}
        virtual ~MouseEvent () {}

        const Geometry::Point &getPosition () const {  return position; }
        void setPosition (const Geometry::Point &position) { this->position = position; }

private:

        Geometry::Point position;

};

}

#	endif /* MOUSE_BAJKA_EVENT_H_ */
