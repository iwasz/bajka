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

        AbstractTween () : forward (true), yoyo (false), repetitions (0), delayMs (0), currentRepetition (0), currentMs (0), state (INIT) {}
        virtual ~AbstractTween () {}

        virtual void update (int deltaMs, bool reverse);

        State getState () const { return state; }

        void start (Manager *m = NULL);

        virtual ITween *repeat (unsigned int num, bool y = false) { repetitions = num; yoyo = y; return this; }
        virtual ITween *delay (unsigned int d) { delayMs = d; return this; }

        virtual void clear ();

protected:

        State transition (State s, bool reverse);

        virtual void initEntry (bool reverse) {}
        virtual void initExit (bool reverse) {}
        virtual void delayEntry (bool reverse) {}
        virtual void delayExit (bool reverse) {}
        virtual void runEntry (bool reverse) {}
        virtual void runExit (bool reverse) {}
        virtual void finishedEntry  (bool reverse) {}
        virtual void finishedExit (bool reverse) {}

        virtual void updateRun (int deltaMs, bool direction) = 0;

        /**
         * Sprawdza czy aktualne powtórzenie się zakończyło. Jeśli tween ma ustawiony repeat,
         * to zostanie on uruchomiony jeszcze raz.
         * @param direction
         * @return
         */
        virtual bool checkEnd (bool direction) = 0;

protected:

        // true forward, false backward
        bool forward;
        bool yoyo;
        unsigned int repetitions;
        unsigned int delayMs;
        unsigned int currentRepetition;
        int currentMs;
        State state;

};

} /* namespace Tween */

#	endif /* ABSTRACTTWEEN_H_ */
