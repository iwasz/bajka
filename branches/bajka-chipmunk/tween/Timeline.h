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

        Timeline () {}
        virtual ~Timeline () {}
        static Timeline *create ();

        void update (int deltaMs, bool reverse);
        Timeline *add (ITween *tween);

private:

        void initExit ();
        void finishedExit ();
        void runEntry ();

        TweenVector tweens;
        TweenVector::iterator current;
        TweenVector::reverse_iterator currentr;

};

extern Timeline *timeline ();

} /* namespace Tween */

#	endif /* TIMELINE_H_ */
