/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MULTITWEEN_H_
#define MULTITWEEN_H_

#include "ITween.h"

namespace Tween {

/**
 * Zawiera kolekcję tweenów i uruchamia je wszystkie naraz.
 */
class MultiTween : public ITween {
public:

        MultiTween () : finished (false) {}
        virtual ~MultiTween () {}
        void update (int deltaMs);
        bool getFinished () const { return finished; }

//private:
public:

        TweenVector tweens;
        bool finished;

};

} /* namespace Tween */

#	endif /* MULTITWEEN_H_ */
