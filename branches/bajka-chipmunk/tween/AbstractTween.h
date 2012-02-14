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

        AbstractTween () : state (INIT), /*started (false), finished (false),*/ yoyo (false), repetitions (0), delayMs (0) {}
        virtual ~AbstractTween () {}

//        bool getFinished () const { return finished; }
//        bool getStarted () const { return started; }
        State getState () const { return state; }

        void start (Manager *m = NULL);

        virtual ITween *repeat (unsigned int num, bool y = false) { repetitions = num; yoyo = y; return this; }
        virtual ITween *delay (unsigned int d) { delayMs = d; return this; }

        virtual void clear ();
//        virtual void rewind ();

protected:

        State state;

        State transition (State s);

        virtual void initEntry () {}
        virtual void initExit () {}
        virtual void delayEntry () {}
        virtual void delayExit () {}
        virtual void forwardEntry () {}
        virtual void forwardExit () {}
        virtual void backwardEntry () {}
        virtual void backwardExit () {}
        virtual void finishedEntry  () {}
        virtual void finishedExit () {}

protected:

        bool yoyo;
        unsigned int repetitions;
        unsigned int delayMs;

};

} /* namespace Tween */

#	endif /* ABSTRACTTWEEN_H_ */
