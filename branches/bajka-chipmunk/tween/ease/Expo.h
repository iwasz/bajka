/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_EXPO_H_
#define BAJKA_EQ_EXPO_H_

#include "IEquation.h"
#include <cmath>

namespace Tween {

class ExpoIn : public IEquation {
public:
        virtual ~ExpoIn () {}

        double compute (double t, double b, double c, double d) const
        {
                return (t == 0) ? (b) : (c * pow (2, 10 * (t / d - 1)) + b);
        }
};

class ExpoOut : public IEquation {
public:
        virtual ~ExpoOut () {}

        double compute (double t, double b, double c, double d) const
        {
                return (t == d) ? (b + c) : (c * (-pow (2, -10 * t / d) + 1) + b);
        }
};

class ExpoInOut : public IEquation {
public:
        virtual ~ExpoInOut () {}

        double compute (double t, double b, double c, double d) const
        {
                if (t == 0) {
                        return b;
                }

                if (t == d) {
                        return b + c;
                }

                if ((t /= d / 2) < 1) {
                        return c / 2 * pow (2, 10 * (t - 1)) + b;
                }

                return c / 2 * (-pow (2, -10 * --t) + 2) + b;
        }
};

} // namespace

#	endif /* CIRC_H_ */
