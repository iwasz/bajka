/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EQ_LINEAR_H_
#define BAJKA_EQ_LINEAR_H_

#include "Equation.h"

namespace Tween {

class Linear : public Equation {
public:
        virtual ~Linear () {}

        double compute (double t, double b, double c, double d) {
                return c * t/d + b;
        }
};

} // namespace

#	endif /* LINEAR_H_ */
