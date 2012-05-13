/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_QUAD_H_
#define BAJKA_EQ_QUAD_H_

#include "IEquation.h"
#include <cmath>

namespace Tween {

class QuadIn : public IEquation {
public:
        virtual ~QuadIn () {}

        double compute (double t, double b, double c, double d) const
        {
                t /= d;
                return c * t * t + b;
        }
};

class QuadOut : public IEquation {
public:
        virtual ~QuadOut () {}

        double compute (double t, double b, double c, double d) const
        {
                t /= d;
                return -c * t * (t - 2) + b;
        }
};

class QuadInOut : public IEquation {
public:
        virtual ~QuadInOut () {}

        double compute (double t, double b, double c, double d) const
        {
                if ((t /= d / 2) < 1) {
                        return c / 2 * t * t + b;
                }

                --t;
                return -c / 2 * (t * (t - 2) - 1) + b;
        }
};

} // namespace

#	endif /* CIRC_H_ */
