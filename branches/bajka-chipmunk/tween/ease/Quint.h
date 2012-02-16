/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_QUINT_H_
#define BAJKA_EQ_QUINT_H_

#include "IEquation.h"
#include <cmath>

namespace Tween {

class QuintIn : public IEquation {
public:
        virtual ~QuintIn () {}

        double compute (double t, double b, double c, double d) const
        {
                t /= d;
                return c * t * t * t * t * t + b;
        }
};

class QuintOut : public IEquation {
public:
        virtual ~QuintOut () {}

        double compute (double t, double b, double c, double d) const
        {
                t = t / d - 1;
                return c * (t * t * t * t * t + 1) + b;
        }
};

class QuintInOut : public IEquation {
public:
        virtual ~QuintInOut () {}

        double compute (double t, double b, double c, double d) const
        {
                if ((t /= d / 2) < 1) {
                        return c / 2 * t * t * t * t * t + b;
                }

                t -= 2;
                return c / 2 * (t * t * t * t * t + 2) + b;
        }
};

} // namespace

#	endif /* CIRC_H_ */
