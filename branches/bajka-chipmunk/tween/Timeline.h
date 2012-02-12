/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_TIMELINE_H_
#define BAJKA_TWEEN_TIMELINE_H_

#include "AbstractTween.h"

namespace Tween {

/**
 * Zawiera kolekcję tweenów i uruchamia je po kolei.
 */
class Timeline : public AbstractTween {
public:

        Timeline () : current (tweens.begin ()) {}
        virtual ~Timeline () {}
        static Timeline *create ();

        void update (int deltaMs);
        Timeline *add (ITween *tween);

private:

        TweenVector tweens;
        TweenVector::iterator current;

};

extern Timeline *timeline ();

} /* namespace Tween */

#	endif /* TIMELINE_H_ */
