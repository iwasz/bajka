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

class IEquation {
public:
        virtual ~IEquation () {}

        /**
         * Computes the next value of the interpolation.
         * @param currentTime  Current time, in seconds.
         * @param initialValue Initial value.
         * @param offset       Offset between target and initial value.
         * @param duration     Total duration, in seconds.
         * @return             Next value.
         */
        virtual double compute (double currentTime, double initialValue, double offset, double duration) const = 0;
};

enum Ease { LINEAR_INOUT,
            QUAD_IN, QUAD_OUT, QUAD_INOUT,
            CUBIC_IN, CUBIC_OUT, CUBIC_INOUT,
            QUART_IN, QUART_OUT, QUART_INOUT,
            QUINT_IN, QUINT_OUT, QUINT_INOUT,
            CIRC_IN, CIRC_OUT, CIRC_INOUT,
            SINE_IN, SINE_OUT, SINE_INOUT,
            EXPO_IN, EXPO_OUT, EXPO_INOUT,
            BACK_IN, BACK_OUT, BACK_INOUT,
            BOUNCE_IN, BOUNCE_OUT, BOUNCE_INOUT,
            ELASTIC_IN, ELASTIC_OUT, ELASTIC_INOUT };

} // namespace

#	endif /* EQUATION_H_ */
