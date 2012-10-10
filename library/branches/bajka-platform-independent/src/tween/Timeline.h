/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_TIMELINE_H_
#define BAJKA_TWEEN_TIMELINE_H_

#include "util/Exceptions.h"
#include "AbstractTween.h"
#include "IMultiTween.h"

namespace Tween {

/**
 * Zawiera kolekcję tweenów i uruchamia je po kolei.
 * \ingroup Tween
 */
class Timeline : public AbstractTween, public IMultiTween {
public:

        Timeline () {}
        virtual ~Timeline () {}

        Timeline *add (ITween *tween);

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
        TweenList::iterator current;
        TweenList::reverse_iterator currentr;

};

extern Timeline *timeline ();

} /* namespace Tween */

#	endif /* TIMELINE_H_ */
