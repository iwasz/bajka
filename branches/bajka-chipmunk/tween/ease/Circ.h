/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_CIRC_H_
#define BAJKA_EQ_CIRC_H_

#include "IEquation.h"
#include <cmath>

namespace Tween {

class CircIn : public IEquation {
public:
        virtual ~CircIn () {}

        double compute (double t, double b, double c, double d) const
        {
                t /= d;
                return -c * (sqrt (1 - t * t) - 1) + b;
        }
};

class CircOut : public IEquation {
public:
        virtual ~CircOut () {}

        double compute (double t, double b, double c, double d) const
        {
                t = t / d - 1;
                return c * sqrt (1 - t * t) + b;
        }
};

class CircInOut : public IEquation {
public:
        virtual ~CircInOut () {}

        double compute (double t, double b, double c, double d) const
        {
                if ((t /= d / 2) < 1) {
                        return -c / 2 * (sqrt (1 - t * t) - 1) + b;
                }

                t -= 2;
                return c / 2 * (sqrt (1 - t * t) + 1) + b;
        }
};

} // namespace

#	endif /* CIRC_H_ */
