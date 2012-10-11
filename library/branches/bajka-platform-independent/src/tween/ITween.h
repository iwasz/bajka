/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_ITWEEN_H_
#define BAJKA_TWEEN_ITWEEN_H_

#include <list>
#include <cstddef>

namespace Tween {
class Manager;
class TweeningProperty;
class IMultiTween;

/**
 * Interfejs tweenów.
 */
class ITween {
public:
        virtual ~ITween () {}

        /**
         * Wykonywane w pętli - uaktualnia tweeny i ustawia targetom własciwiści (tweening properties).
         */
        virtual void update (int deltaMs, bool reverse) = 0;

        /**
         * Stan tweena.
         * \see ITween::getState
         */
        enum State { INIT, DELAY, RUN, FINISHED, END };

        /**
         * Zwraca aktualny stan tweena (czy zatrzymany, czy aktualnie wykonywany etc).
         */
        virtual State getState () const = 0;

        /**
         * Dodaje tween do managera, który zaczyna go natychmiast wykonywać.
         */
        virtual void start () = 0;

        /**
         * Ustawia ilość powtórzeń (0 oznacza brak powótrzeń, czyli tween wykopna się raz, 1
         * oznacza bazowy tween + jego powtórkę = razem 2 sekwencje).
         */
        virtual ITween *repeat (unsigned int num, bool yoyo = false) = 0;

        /**
         * Opóźnienie startu w ms.
         */
        virtual ITween *delay (unsigned int duration) = 0;

        /**
         * Czas sekwencji animacji w milisekundach - nie wszystkie konkretne klasy tweenów implementują
         * tą metodę - IMultiTweeny zwracają tutaj -1.
         */
        virtual int getDurationMs () const = 0;

        /**
         * Czas sekwencji animacji w milisekundach - nie wszystkie konkretne klasy tweenów implementują
         * tą metodę - IMultiTweeny zrzucają tu wyjątek.
         */
        virtual void setDurationMs (int ms) = 0;

        virtual void remove (void const *target, bool onlyActive = false) = 0;
        virtual void remove (void const *target, TweeningProperty *property, bool onlyActive = false) = 0;

        virtual void setParent (IMultiTween *p) = 0;
};

typedef std::list <ITween *> TweenList;

} /* namespace Tween */

#	endif /* ITWEEN_H_ */
