/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_BACK_H_
#define BAJKA_EQ_BACK_H_

#include "IEquation.h"

namespace Tween {

namespace {
const double BACK_SCALE = 1.70158;
}

class BackIn : public IEquation {
public:
        virtual ~BackIn () {}

        double compute (double t, double b, double c, double d) const
        {
                t /= d;
                return c * t * t * ((BACK_SCALE + 1) * t - BACK_SCALE) + b;
        }
};

class BackOut : public IEquation {
public:
        virtual ~BackOut () {}

        double compute (double t, double b, double c, double d) const
        {
                t = t / d - 1;
                return c * (t * t * ((BACK_SCALE + 1) * t + BACK_SCALE) + 1) + b;
        }
};

class BackInOut : public IEquation {
public:
        virtual ~BackInOut () {}

        double compute (double t, double b, double c, double d) const
        {
                double s = BACK_SCALE * 1.525;

                if ((t /= d / 2) < 1) {
                        return c / 2 * (t * t * ((s + 1) * t - s)) + b;
                }

                t -= 2;
                return c / 2 * (t * t * ((s + 1) * t + s) + 2) + b;
        }
};

} // namespace

#	endif /* BACK_H_ */
