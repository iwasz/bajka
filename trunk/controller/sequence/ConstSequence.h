/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONST_SEQUENCE_H_
#define CONST_SEQUENCE_H_

#include <Reflection.h>

#include "ISequence.h"
#include "geometry/Point.h"

namespace Controller {

/**
 * Stała sekwencja - zawsze zwraca step.
 * \ingroup Sequence
 */
template <typename T>
class ConstSequence : public ISequence <T> {
public:
        __c (void)

        ConstSequence () : step (0.0) {}

        virtual ~ConstSequence () {}

        bool hasNext () const { return true; }
        const T &next () const  { return step; }

/*--------------------------------------------------------------------------*/

        const T &getStep () const { return step; }
        _m (setStep) void setStep (const T &step) { this->step = step; }

private:

        T step;

        _tb
//        _t (ConstSequence<double>)
        _t (ConstSequence<Geometry::Point>)
        _te
};

}

#	endif /* STEPSEQUENCE_H_ */
