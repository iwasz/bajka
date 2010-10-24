/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTOBSERVER_H_
#define ABSTRACTOBSERVER_H_

#include <numeric>
#include "IObserver.h"

namespace Event {

/**
 * Obserwator z zaimplementowanymi powtarzalnymi metodami - klasa
 * ułątwiająca implementowanie obserwatorów. Nie można jej zinstancjonować.
 * \ingroup Events
 */
class AbstractObserver : public virtual IObserver {
public:

        __c (void)

        AbstractObserver () : bitMask (std::numeric_limits <unsigned int>::max ()), active (true) {}
        virtual ~AbstractObserver () {}

        virtual bool onEvent (IEvent *event);

        /// Sprawdza, czy ten obserwer jest zainteresowany danym wyjątkiem.
        virtual bool acceptEvent (IEvent *event) const;

        bool getActive () const { return active; }
        _m (setActive) void setActive (bool a) { active = a; }

        virtual bool onButtonPress (ButtonPressEvent *e) { return true; }
        virtual bool onButtonRelease (ButtonReleaseEvent *e) { return true; }
        virtual bool onMouseMotion (MouseMotionEvent *e) { return true; }
        virtual bool onKeyDown (KeyDownEvent *e) { return true; }
        virtual bool onKeyUp (KeyUpEvent *e) { return true; }
        virtual bool onTimer (TimerEvent *e) { return true; }
        virtual bool onQuit (QuitEvent *e) { return true; }

/*--------------------------------------------------------------------------*/

        // TODO EventBitMask, a nie bitMask
        unsigned int getBitMask () const { return bitMask; }
        _m (setBitMask) void setBitMask (unsigned int b) { bitMask = b; }

public:

        unsigned int bitMask;
        bool active;

        _e (AbstractObserver)
};

}

#	endif /* ABSTRACTOBSERVER_H_ */
