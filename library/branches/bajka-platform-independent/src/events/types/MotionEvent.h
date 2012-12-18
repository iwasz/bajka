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

        /// Współrzędne ekranowe kursora.
        Geometry::Point position;
        /// Przesunięcie kursora w stosunku do poprzendiego punktu.
        Geometry::Point movement;
        /// Siła nacisku.
        float pressure;
        /// Rozmiar punktu.
        float size;
        /// Słuzy do rozróżniania pointerów. Dla myszki nie ma znaczenia, bo 1 pointer.
        int32_t id;
};

/**
 * Źródło eventu.
 */
enum MotionSource {
        MOUSE,  //!< Mysz - jeden pointer, ale wile guzików.
        TOUCH,  //!< Ekran dotykowy - wiele pointerów, kazdy po jednmym "guziku", nie można odrywać palca od ekranu poczas ruchu (w szczególnosci nie działa onMotionOver i Out).
        OTHER   //!< Inne.
};

/**
 * Event związany myszą lub z ekranem dotykowym. Dane pogrupowane są na kursory. Kiedy
 * podłączona jest mysz, to kursor jest tylko jeden. Kiedy używamy ekranu dotykowego,
 * kursorów jest tyle ile palców dotykających ekranu.
 * \ingroup Events
 */
class MotionEvent : public IEvent {
public:

        MotionEvent ();
        virtual ~MotionEvent () {}

        /*
         * Dodatkowe klawisze na klawiaturze naciśnięte podczas tego eventu (takie jak ALT, CTRL etc).
         * Działa tylko na Androidzie.
         */
        KeyMod getMetaState () const { return metaState; }
        void setMetaState (KeyMod metaState) { this->metaState = metaState; }

        /**
         * Liczba naciśniętych przycisków myszy lub, liczba pointerów na ekranie dotykowym (liczba
         * palców dotykających ekranu).
         */
        int getPointerCount () const { return pointerCount; }
        void setPointerCount (int pointerCount) { this->pointerCount = pointerCount; }

        /**
         * Maska bitowa zawierająca informację o naciśniętych przyciskach myszy, albo o
         * aktywnych pointerach na ekranie dotykowym. Można testowac z wartościami z enumu
         * MotionPointer.
         */
        uint32_t getButtons () const { return buttons; }
        void setButtons (uint32_t buttons) { this->buttons = buttons; }

        /**
         * Zwraca pointer o danym indeksie. Nie dokonuje
         */
        MotionPointer const &getPointer (unsigned int i) const;
        MotionPointer &getPointer (unsigned int i);

        MotionSource getSource () const { return source; }
        void setSource (MotionSource s) { source = s; }

        virtual std::string toString () const;

private:

        KeyMod metaState;
        int pointerCount;
        uint32_t buttons;
        MotionSource source;
        MotionPointer pointers[MAX_POINTERS];
};

} // namespace Event

#	endif /* MOUSE_BAJKA_EVENT_H_ */
