/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Bounce.h"

namespace Tween {

double BounceOut::cmp (double t, double b, double c, double d)
{
        if ((t /= d) < (1 / 2.75)) {
                return c * (7.5625 * t * t) + b;
        } else if (t < (2 / 2.75)) {
                t -= (1.5 / 2.75);
                return c * (7.5625 * t * t + 0.75) + b;
        } else if (t < (2.5 / 2.75)) {
                t -= (2.25 / 2.75);
                return c * (7.5625 * t * t + 0.9375) + b;
        } else {
                t -= (2.625 / 2.75);
                return c * (7.5625 * t * t + 0.984375) + b;
        }
}

/****************************************************************************/

double BounceIn::cmp (double t, double b, double c, double d)
{
        return c - BounceOut::cmp (d - t, 0, c, d) + b;
}


} /* namespace Tween */
