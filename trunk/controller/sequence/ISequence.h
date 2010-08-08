/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ISEQUENCE_H_
#define ISEQUENCE_H_

#include <Object.h>

namespace Controller {

/**
 * ISequence interface is a relatively simple concept similar to java
 * Iterator. Its concrete classes implements a sequence of values. It
 * is meant to be used to introduce animated objects - for example as
 * animation frame number generator (sequence of frames) etc.
 *
 * Unfortunately, but ISequence must inherit from Core::Object due to
 * variant_cast issues.
 *
 * \ingroup Sequence
 */
template <typename T>
struct ISequence : public Core::Object {
        virtual ~ISequence () {}

        /**
         * Czy sekwencja wygeneruje następną wartość?
         * @return Czy sekwencja wygeneruje następną wartość?
         */
        virtual bool hasNext () const = 0;

        /**
         * Natępna wartość generowana przez sekwencję. Jest to klasa szablonowa,
         * więc zwracana wartość może być dowolna.
         * @return Wartość z sekwensji.
         */
        virtual const T &next () const = 0;

};

}

#	endif /* ISEQUENCE_H_ */
