/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STEPSEQUENCE_H_
#define STEPSEQUENCE_H_

#include <Reflection.h>

#include "ISequence.h"
#include "geometry/Point.h"

namespace Controller {

/**
 * Simple (test) sequence.
 */
template <typename T>
class StepSequence : public ISequence <T> {
public:
        __c (void)

        StepSequence () : current (0.0), initial (0.0), step (0.0), decrement (false), stepNumber (0), currentStep (0) {}

        virtual ~StepSequence () {}

        bool hasNext () const { return true; }
        const T &next () const;

/*--------------------------------------------------------------------------*/

        const T &getCurrent () const { return current; }
        _m (setCurrent) void setCurrent (const T &current) { this->current = current; }

        bool getDecrement () const { return decrement; }
        _m (setDecrement) void setDecrement (bool decrement) { this->decrement = decrement; }

        const T &getInitial () const { return initial; }
        _m (setInitial) void setInitial (const T &initial) { this->initial = initial; current = initial; }

        const T &getStep () const { return step; }
        _m (setStep) void setStep (const T &step) { this->step = step; }

        int getStepNumber () const { return stepNumber; }
        _m (setStepNumber) void setStepNumber (int stepNumber) { this->stepNumber = stepNumber; }

private:

        mutable T current;
        T initial;
        T step;
        bool decrement;
        int stepNumber;
        mutable int currentStep;

        _tb
        _t (StepSequence<double>)
        _t (StepSequence<Geometry::Point>)
        _te
};

/****************************************************************************/

template <typename T>
const T &StepSequence <T>::next () const
{
        if (++currentStep >= stepNumber) {
                current = initial;
                currentStep = 0;
                return current;
        }

        if (!decrement) {
                current += step;
        }
        else {
                current -= step;
        }

        return current;
}

}

#	endif /* STEPSEQUENCE_H_ */
