/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Timeline.h"

namespace Tween {

void Timeline::update (int deltaMs)
{
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
}

} /* namespace Tween */
