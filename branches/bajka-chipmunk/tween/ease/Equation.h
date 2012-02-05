/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_EQUATION_H_
#define BAJKA_TWEEN_EQUATION_H_

namespace Tween {

class Equation {
public:
        virtual ~Equation () {}

        /**
         * Computes the next value of the interpolation.
         * @param currentTime  Current time, in seconds.
         * @param initialValue Initial value.
         * @param offset       Offset between target and initial value.
         * @param duration     Total duration, in seconds.
         * @return             Next value.
         */
        virtual double compute (double currentTime, double initialValue, double offset, double duration) = 0;
};

} // namespace

#	endif /* EQUATION_H_ */
