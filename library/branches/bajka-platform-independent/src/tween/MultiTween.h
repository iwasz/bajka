/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MULTITWEEN_H_
#define BAJKA_MULTITWEEN_H_

#include "util/Exceptions.h"
#include "AbstractTween.h"
#include "IMultiTween.h"

namespace Tween {

/**
 * Zawiera kolekcję tweenów i uruchamia je jednocześnie. Kończy swoją pracę, kiedy
 * ostatni z tweenów zakończy działanie. Jest dopełnieniem Timeline. Timeline uruchamia
 * szeregowo, a MultiTween równolegle.
 * \ingroup Tween
 */
class MultiTween : public AbstractTween, public IMultiTween {
public:

        virtual ~MultiTween () {}

        IMultiTween *add (ITween *tween);
        void remove (ITween *tween);
        void remove (void const *target, bool onlyActive = false);
        void remove (void const *target, TweeningProperty *property, bool onlyActive = false);

        int getDurationMs () const { return -1; }
        void setDurationMs (int ms) { throw Util::OperationNotSupportedException (); }

        void setParent (IMultiTween *p) {}

private:

        void initExit (bool reverse);
        void finishedExit (bool reverse);
        void runEntry (bool reverse);
        void updateRun (int deltaMs, bool direction);
        bool checkEnd (bool direction);

private:

        TweenList tweens;

};

extern MultiTween *multi ();

} /* namespace Tween */

#	endif /* MULTITWEEN_H_ */
