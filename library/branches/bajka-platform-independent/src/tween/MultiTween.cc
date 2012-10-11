/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MultiTween.h"
#include "Manager.h"

namespace Tween {

MultiTween *multi ()
{
        return Manager::getMain ()->newMultiTween ();
}

/*##########################################################################*/

void MultiTween::updateRun (int deltaMs, bool direction)
{
        for (TweenList::iterator i = tweens.begin (); i != tweens.end (); ++i) {
                (*i)->update (deltaMs, !direction);
        }
}

/****************************************************************************/

bool MultiTween::checkEnd (bool direction)
{
        bool end = true;

        for (TweenList::iterator i = tweens.begin (); i != tweens.end (); ++i) {
                if ((*i)->getState () != END) {
                        end = false;
                        break;
                }
        }

        return end;
}
/****************************************************************************/

IMultiTween *MultiTween::add (ITween *tween)
{
        tween->setParent (this);
        tweens.push_back (tween);
        return this;
}

/****************************************************************************/

void MultiTween::remove (ITween *tween)
{
        tweens.remove (tween);
        Manager::getMain ()->free (tween);
}

/****************************************************************************/

void MultiTween::remove (void const *target, bool onlyActive)
{
        for (TweenList::iterator i = tweens.begin (); i != tweens.end (); ++i) {
                (*i)->remove (target, onlyActive);
        }
}

/****************************************************************************/

void MultiTween::remove (void const *target, TweeningProperty *property, bool onlyActive)
{
        for (TweenList::iterator i = tweens.begin (); i != tweens.end (); ++i) {
                (*i)->remove (target, property, onlyActive);
        }
}

} /* namespace Tween */
