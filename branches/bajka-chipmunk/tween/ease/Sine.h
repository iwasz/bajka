/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_SINE_H_
#define BAJKA_EQ_SINE_H_

#include "IEquation.h"
#include <cmath>

namespace Tween {

class SineIn : public IEquation {
public:
        virtual ~SineIn () {}

        double compute (double t, double b, double c, double d) const
        {
                return -c * cos (t / d * (M_PI / 2)) + c + b;
        }
};

class SineOut : public IEquation {
public:
        virtual ~SineOut () {}

        double compute (double t, double b, double c, double d) const
        {
                return c * sin (t / d * (M_PI / 2)) + b;
        }
};

class SineInOut : public IEquation {
public:
        virtual ~SineInOut () {}

        double compute (double t, double b, double c, double d) const
        {
                return -c / 2 * (cos (M_PI * t / d) - 1) + b;
        }
};

} // namespace

#	endif /* CIRC_H_ */
