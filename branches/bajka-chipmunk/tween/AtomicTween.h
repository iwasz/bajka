/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ATOMICTWEEN_H_
#define ATOMICTWEEN_H_

#include <cstddef>
#include <memory>
#include "ease/IEquation.h"
#include "accessor/IAccessor.h"
#include "AbstractTween.h"

namespace Tween {

/**
 * Tween dla pojedynczej wartości (na przykład współrzędnej X w punkcie).
 */
class AtomicTween : public AbstractTween {
public:

        virtual ~AtomicTween () {}
        static AtomicTween *create ();

        void update (int deltaMs);

        friend AtomicTween *to (void *targetObject, unsigned int durationMs, Ease ease);
        AtomicTween *abs (unsigned int property, double value) { return target (property, value, true); }
        AtomicTween *rel (unsigned int property, double value) { return target (property, value, false); }

protected:

        AtomicTween () : AbstractTween (), equation (NULL), accessor (NULL), durationMs (0), currentMs (0), startValue (0), targetValue (0), object (NULL), absolute (true)  {}
        void addTween (ITween *tween);
        AtomicTween *target (unsigned int property, double value, bool abs);

        // Uruchamia się jeden raz na poczatku działania tweena (lub po repeat).
        void init ();

private:

        IEquation const *equation;
        IAccessor const *accessor;
        unsigned int durationMs;
        unsigned int currentMs;
        double startValue;
        double targetValue;
        void *object;
        bool absolute;
        std::auto_ptr <TweenVector> tweens;

};

/**
 *
 * @param targetObject
 * @param durationMs
 * @param ease
 * @return
 */
extern AtomicTween *to (void *targetObject, unsigned int durationMs, Ease ease = LINEAR_INOUT);

}

#	endif /* ATOMICTWEEN_H_ */
