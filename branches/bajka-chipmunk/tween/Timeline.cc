/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Timeline.h"

namespace Tween {

Timeline *timeline ()
{
        return Timeline::create ();
}

/****************************************************************************/

Timeline *Timeline::create ()
{
        // TODO pool
        return new Timeline;
}

/****************************************************************************/

void Timeline::update (int deltaMs)
{
#if 0

        if (finished || tweens.empty ()) {
                return;
        }

        (*current)->update (deltaMs);

        if ((*current)->getFinished ()) {
                if (++current == tweens.end ()) {
                        finished = true;
                        return;
                }
        }
#endif
}

/****************************************************************************/

Timeline *Timeline::add (ITween *tween)
{
        tweens.push_back (tween);
        current = tweens.begin ();
        return this;
}

} /* namespace Tween */
