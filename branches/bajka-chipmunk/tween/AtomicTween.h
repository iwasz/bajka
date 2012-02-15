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

        struct Target {

                Target () : accessor (NULL), tween (NULL), startValue (0), endValue (0), absolute (true) {}

                // TODO pula
                static Target *create () { return new Target; }

                void clear ();
                void init ();
                void update ();

                IAccessor const *accessor;
                AtomicTween *tween;
                double startValue;
                double endValue;
                bool absolute;
        };

        typedef std::vector <Target *> TargetVector;

        virtual ~AtomicTween () {}
        static AtomicTween *create ();

        friend AtomicTween *to (void *targetObject, unsigned int durationMs, Ease ease);
        AtomicTween *abs (unsigned int property, double value) { return target (property, value, true); }
        AtomicTween *rel (unsigned int property, double value) { return target (property, value, false); }

        void clear ();

protected:

        AtomicTween () : AbstractTween (), equation (NULL), durationMs (0), object (NULL)  {}
        AtomicTween *target (unsigned int property, double value, bool abs);

        // Uruchamia się jeden raz na poczatku działania tweena (lub po repeat).
        void initEntry (bool reverse);
        void initExit (bool reverse);
        void delayEntry (bool reverse);
        void delayExit (bool reverse);
        void runEntry (bool reverse);
        void runExit (bool reverse);
        void finishedEntry (bool reverse);
        void finishedExit (bool reverse);

        void updateRun (int deltaMs, bool direction);
        bool checkEnd (bool direction);

private:

        IEquation const *equation;
        int durationMs;
        void *object;
        TargetVector targets;
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