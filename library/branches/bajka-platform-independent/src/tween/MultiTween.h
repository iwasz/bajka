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

        MultiTween *add (ITween *tween)
        {
                tweens.push_back (tween);
                return this;
        }

        int getDurationMs () const { return -1; }
        void setDurationMs (int ms) { throw Util::OperationNotSupportedException (); }

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
