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

/**
 * Wartości przedstawiające guziki myszy. Można z nich robić maskę bitową.
 */
enum MouseButton {
        LEFT =    0x01, /// Lewy guzik myszy
        CENTER =  0x02, /// Środkowy guzik myszy
        RIGHT =   0x04, /// Prawy guzik myszy
        BUTTON4 = 0x08, /// Guzik numer 4
        BUTTON5 = 0x10, /// Guzik numer 5
        BUTTON6 = 0x20, /// Guzik numer 6
        BUTTON7 = 0x40, /// Guzik numer 7
        BUTTON8 = 0x80  /// Guzik numer 8
};

/**
 * Event związany jakoś z myszą.
 * \ingroup Events
 */
class MouseEvent : public AbstractEvent {
public:

        MouseEvent () {}
        MouseEvent (const Geometry::Point &position) : position (position) {}
        virtual ~MouseEvent () {}

        /// Współrzędne ekranowe kursora.
        const Geometry::Point &getPosition () const {  return position; }
        /// Współrzędne ekranowe kursora.
        void setPosition (const Geometry::Point &position) { this->position = position; }

private:

        Geometry::Point position;

};

}

#	endif /* MOUSE_BAJKA_EVENT_H_ */
