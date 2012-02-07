/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_TIMELINE_H_
#define BAJKA_TWEEN_TIMELINE_H_

#include "ITween.h"

namespace Tween {

/**
 * Zawiera kolekcję tweenów i uruchamia je po kolei.
 */
class Timeline : public ITween {
public:

        Timeline () : current (tweens.begin ()), finished (false) {}
        virtual ~Timeline () {}
        void update (int deltaMs);
        bool getFinished () const { return finished; }

//private:
public:

        TweenVector tweens;
        TweenVector::iterator current;
        bool finished;

};

} /* namespace Tween */

#	endif /* TIMELINE_H_ */
