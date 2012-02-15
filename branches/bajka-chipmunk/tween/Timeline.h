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

        Timeline *add (ITween *tween);

private:

        void initExit (bool reverse);
        void finishedExit (bool reverse);
        void runEntry (bool reverse);
        void updateRun (int deltaMs, bool direction);
        bool checkEnd (bool direction);

private:

        TweenVector tweens;
        TweenVector::iterator current;
        TweenVector::reverse_iterator currentr;

};

extern Timeline *timeline ();

} /* namespace Tween */

#	endif /* TIMELINE_H_ */
