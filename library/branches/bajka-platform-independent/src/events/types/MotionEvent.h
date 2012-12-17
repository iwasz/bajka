/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MOUSE_BAJKA_EVENT_H_
#define MOUSE_BAJKA_EVENT_H_

#include "IEvent.h"
#include "geometry/Point.h"
#include "KeyCode.h"
#include <stdint.h>

namespace Event {

#define MAX_POINTERS 10

/**
 * Wartości przedstawiające guziki myszy. Można z nich robić maskę bitową.
 */
enum MotionButton {
        BUTTON0 = 1 << 0, //!< Lewy guzik myszy lub pierwszy pointer ekranu dotykowego
        BUTTON1 = 1 << 1, //!< Środkowy guzik myszy lub drugi pointer ekranu dotykowego
        BUTTON2 = 1 << 2, //!< Prawy guzik myszy lub trzeci pointer ekranu dotykowego
        BUTTON3 = 1 << 3,
        BUTTON4 = 1 << 4,
        BUTTON5 = 1 << 5,
        BUTTON6 = 1 << 6,
        BUTTON7 = 1 << 7,
        BUTTON8 = 1 << 8,
        BUTTON9 = 1 << 0
};

/**
 * Pojedynczy pointer.
 */
struct MotionPointer {

        MotionPointer ();

        float x;
        float y;
        float offsetX;
        float offsety;
        float pressure;
        float size;
};

/**
 * Event związany jakoś z myszą.
 * \ingroup Events
 */
class MotionEvent : public IEvent {
public:

        MotionEvent ();
        virtual ~MotionEvent () {}

        /// Współrzędne ekranowe kursora.
        const Geometry::Point &getPosition () const {  return position; }

        /*
         * Dodatkowe klawisze na klawiaturze naciśnięte podczas tego eventu (takie jak ALT, CTRL etc).
         * Działa tylko na Androidzie.
         */
        KeyMod getMetaState () const { return metaState; }

        /**
         * Liczba naciśniętych przycisków myszy lub, liczba pointerów na ekranie dotykowym (liczba
         * palców dotykających ekranu).
         */
        int getPointerCount () const { return pointerCount; }

        /**
         * Maska bitowa zawierająca informację o naciśniętych przyciskach myszy, albo o
         * aktywnych pointerach na ekranie dotykowym. Można testowac z wartościami z enumu
         * MotionPointer.
         */
        uint32_t getButtons () const { return buttons; }

        /**
         * Zwraca pointer o danym indeksie. Nie dokonuje
         */
        MotionPointer const &getPointer (unsigned int i) const;

private:

        /// Współrzędne ekranowe kursora.
        void setPosition (const Geometry::Point &position) { this->position = position; }

private:

        Geometry::Point position;
        KeyMod metaState;
        int pointerCount;
        uint32_t buttons;
        MotionPointer pointers[MAX_POINTERS];
};

} // namespace Event

#	endif /* MOUSE_BAJKA_EVENT_H_ */
