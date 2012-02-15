/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_BOUNCE_H_
#define BAJKA_EQ_BOUNCE_H_

#include "IEquation.h"

namespace Tween {

class BounceOut : public IEquation {
public:
        virtual ~BounceOut () {}
        double compute (double t, double b, double c, double d) const { return cmp (t, b, c, d); }
        static double cmp (double t, double b, double c, double d);
};

class BounceIn : public IEquation {
public:
        virtual ~BounceIn () {}
        double compute (double t, double b, double c, double d) const { return cmp (t, b, c, d); }
        static double cmp (double t, double b, double c, double d);
};

class BounceInOut : public IEquation {
public:
        virtual ~BounceInOut () {}

        double compute (double t, double b, double c, double d) const
        {
                if (t < d / 2) {
                        return BounceIn::cmp (t * 2, 0, c, d) * 0.5 + b;
                }

                return BounceOut::cmp (t * 2 - d, 0, c, d) * 0.5 + c * 0.5 + b;
        }
};

} /* namespace Tween */

#	endif /* BOUNCE_H_ */
