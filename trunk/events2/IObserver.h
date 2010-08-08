/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <Object.h>
#include <Reflection.h>
#include <collection/List.h>
#include <collection/Vector.h>

namespace Event {
class IEvent;
class ButtonPressEvent;
class ButtonReleaseEvent;
class MouseMotionEvent;
class KeyDownEvent;
class KeyUpEvent;
class TimerEvent;
class QuitEvent;

/**
 * IObserver
 * TODO Nie jest napisane co oznacza wartość zwracana z metod.
 * \ingroup Events
 */
struct IObserver : public virtual Core::Object {

        virtual ~IObserver () {}
        virtual bool onEvent (IEvent *event) = 0;

        /// Sprawdza, czy ten obserwer jest zainteresowany danym wyjątkiem.
        virtual bool acceptEvent (IEvent *event) const = 0;

        /**
         * Mówi, czy ten obserwator jest w ogóle aktywny. Jeśli zwróci false,
         * to żadna prodecura obsługi nie zostanie wykonana.
         * @return Czy aktywny.
         */
        virtual bool getActive () const = 0;

        virtual bool onButtonPress (ButtonPressEvent *e) = 0;
        virtual bool onButtonRelease (ButtonReleaseEvent *e) = 0;
        virtual bool onMouseMotion (MouseMotionEvent *e) = 0;
        virtual bool onKeyDown (KeyDownEvent *e) = 0;
        virtual bool onKeyUp (KeyUpEvent *e) = 0;
        virtual bool onTimer (TimerEvent *e) = 0;
        virtual bool onQuit (QuitEvent *e) = 0;
};

typedef Reflection::List <Ptr <IObserver> > ObserverList;
_f (ObserverList)

typedef Reflection::List <Ptr <IObserver> > ObserverVector;
_f (ObserverVector)

}

#	endif /* OBSERVER_H_ */
