/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_LINEAR_H_
#define BAJKA_EQ_LINEAR_H_

#include "IEquation.h"

namespace Tween {

class Linear : public IEquation {
public:
        virtual ~Linear () {}

        double compute (double t, double b, double c, double d) const
        {
                return c * t/d + b;
        }
};

} // namespace

#	endif /* LINEAR_H_ */
