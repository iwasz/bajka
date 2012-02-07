/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ATOMICTWEEN_H_
#define ATOMICTWEEN_H_

#include "ITween.h"
#include "ease/IEquation.h"
#include "accessor/IAccessor.h"
#include <cstddef>

namespace Tween {

/**
 * Tween dla pojedynczej wartości (na przykład współrzędnej X w punkcie).
 */
class AtomicTween : public ITween {
public:

		AtomicTween () : equation (NULL), accessor (NULL), durationMs (0), currentMs (0), startValue (0), targetValue (0), object (NULL), finished (false) {}
        virtual ~AtomicTween () {}
        void update (int deltaMs);

//private:
public:

        IEquation *equation;
        IAccessor *accessor;
        unsigned int durationMs;
        unsigned int currentMs;
        double startValue;
        double targetValue;
        void *object;
        bool finished;
};

}

#	endif /* ATOMICTWEEN_H_ */
