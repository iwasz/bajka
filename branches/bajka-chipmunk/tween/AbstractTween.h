/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTTWEEN_H_
#define ABSTRACTTWEEN_H_

#include "ITween.h"
#include <cstddef>

namespace Tween {
class Manager;

class AbstractTween : public ITween {
public:

        AbstractTween () : currentDirection (true), yoyo (false), repetitions (0), delayMs (0), currentRepetition (0), state (INIT) {}
        virtual ~AbstractTween () {}

        State getState () const { return state; }

        void start (Manager *m = NULL);

        virtual ITween *repeat (unsigned int num, bool y = false) { repetitions = num; yoyo = y; return this; }
        virtual ITween *delay (unsigned int d) { delayMs = d; return this; }

        virtual void clear ();

protected:

        State transition (State s);

        virtual void initEntry () {}
        virtual void initExit () {}
        virtual void delayEntry () {}
        virtual void delayExit () {}
        virtual void runEntry () {}
        virtual void runExit () {}
        virtual void finishedEntry  () {}
        virtual void finishedExit () {}

protected:

        // true forward, false backward
        bool currentDirection;
        bool yoyo;
        unsigned int repetitions;
        unsigned int delayMs;
        unsigned int currentRepetition;
        State state;

};

} /* namespace Tween */

#	endif /* ABSTRACTTWEEN_H_ */
