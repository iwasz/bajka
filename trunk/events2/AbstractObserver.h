/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTOBSERVER_H_
#define ABSTRACTOBSERVER_H_

#include "IObserver.h"

namespace Event {

/**
 *
 */
class AbstractObserver : public IObserver {
public:

        AbstractObserver () : bitMask (0) {}
        virtual ~AbstractObserver () {}

        virtual bool onEvent (IEvent *event);

        /// Sprawdza, czy ten obserwer jest zainteresowany danym wyjątkiem.
        virtual bool acceptEvent (IEvent *event) const;

        virtual bool onButtonPress (ButtonPressEvent *e) { return true; }
        virtual bool onButtonRelease (ButtonReleaseEvent *e) { return true; }
        virtual bool onMouseMotion (MouseMotionEvent *e) { return true; }
        virtual bool onKeyDown (KeyDownEvent *e) { return true; }
        virtual bool onKeyUp (KeyUpEvent *e) { return true; }
        virtual bool onTimer (TimerEvent *e) { return true; }
        virtual bool onQuit (QuitEvent *e) { return true; }

/*--------------------------------------------------------------------------*/

        unsigned int getBitMask () const { return bitMask; }
        void setBitMask (unsigned int b) { bitMask = b; }

public:

        unsigned int bitMask;
};

}

#	endif /* ABSTRACTOBSERVER_H_ */
