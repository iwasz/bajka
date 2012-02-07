/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MultiTween.h"

namespace Tween {

void MultiTween::update (int deltaMs)
{
        if (finished) {
                return;
        }

        for (TweenVector::iterator i = tweens.begin (); i != tweens.end (); ++i) {
                (*i)->update (deltaMs);
                finished |= !(*i)->getFinished ();
        }

        finished = !finished;
}

} /* namespace Tween */
