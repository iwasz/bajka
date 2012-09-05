/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_ELASTIC_H_
#define BAJKA_EQ_ELASTIC_H_

#include "IEquation.h"
#include <cmath>

namespace Tween {

class ElasticIn : public IEquation {
public:
        virtual ~ElasticIn () {}

        double compute (double t, double b, double c, double d) const
        {
                if (t == 0.0) {
                        return b;
                }

                if ((t /= d) == 1) {
                        return b + c;
                }

                double p = d * 0.3;
                double s = p / 4;
                t-=1;
                return -(c * pow (2, 10 * t) * sin ((t * d - s) * (2 * M_PI) / p)) + b;
        }
};

class ElasticOut : public IEquation {
public:
        virtual ~ElasticOut () {}

        double compute (double t, double b, double c, double d) const
        {
                if (t == 0) {
                        return b;
                }

                if ((t /= d) == 1) {
                        return b + c;
                }

                double p = d * 0.3;
                double s = p / 4;
                return (c * pow (2, -10 * t) * sin ((t * d - s) * (2 * M_PI) / p) + c + b);
        }
};

class ElasticInOut : public IEquation {
public:
        virtual ~ElasticInOut () {}

        double compute (double t, double b, double c, double d) const
        {
                if (t == 0) {
                        return b;
                }

                if ((t /= d / 2) == 2) {
                        return b + c;
                }

                double p = d * (0.3 * 1.5);
                double s = p / 4;

                if (t < 1) {
                        t -= 1;
                        return -0.5 * (c * pow (2, 10 * t) * sin ((t * d - s) * (2 * M_PI) / p)) + b;
                }

                t -= 1;
                return c * pow (2, -10 * t) * sin ((t * d - s) * (2 * M_PI) / p) * 0.5 + c + b;
        }
};

} // namespace

#	endif /* CIRC_H_ */
