/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_QUART_H_
#define BAJKA_EQ_QUART_H_

#include "IEquation.h"
#include <cmath>

namespace Tween {

class QuartIn : public IEquation {
public:
        virtual ~QuartIn () {}

        double compute (double t, double b, double c, double d) const
        {
                t /= d;
                return c * t * t * t * t + b;
        }
};

class QuartOut : public IEquation {
public:
        virtual ~QuartOut () {}

        double compute (double t, double b, double c, double d) const
        {
                t = t / d - 1;
                return -c * (t * t * t * t - 1) + b;
        }
};

class QuartInOut : public IEquation {
public:
        virtual ~QuartInOut () {}

        double compute (double t, double b, double c, double d) const
        {
                if ((t /= d / 2) < 1) {
                        return c / 2 * t * t * t * t + b;
                }

                t -= 2;
                return -c / 2 * (t * t * t * t - 2) + b;
        }
};

} // namespace

#	endif /* CIRC_H_ */
