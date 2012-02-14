/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_CUBIC_H_
#define BAJKA_EQ_CUBIC_H_

#include "IEquation.h"

namespace Tween {

class CubicIn : public IEquation {
public:
        virtual ~CubicIn () {}

        double compute (double t, double b, double c, double d) const {
                t /= d;
                return c * t * t * t + b;
        }
};

class CubicOut : public IEquation {
public:
        virtual ~CubicOut () {}

        double compute (double t, double b, double c, double d) const {
                t = t / d - 1;
                return c * (t * t * t + 1) + b;
        }
};

class CubicInOut : public IEquation {
public:
        virtual ~CubicInOut () {}

        double compute (double t, double b, double c, double d) const {
                if ((t /= d / 2) < 1) {
                        return c / 2 * t * t * t + b;
                }

                t -= 2;
                return c / 2 * (t * t * t + 2) + b;
        }
};

} // namespace

#	endif /* CUBIC_H_ */
