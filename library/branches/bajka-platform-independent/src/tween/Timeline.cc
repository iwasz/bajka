/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Timeline.h"
#include "Manager.h"

namespace Tween {

Timeline *timeline ()
{
        return Manager::getMain ()->newTimeline ();
}

/****************************************************************************/

void Timeline::initExit (bool reverse)
{
        currentRepetition = repetitions;
}

/****************************************************************************/

void Timeline::finishedExit (bool reverse)
{
        currentRepetition = repetitions;
}

/****************************************************************************/

void Timeline::runEntry (bool reverse)
{
        current = tweens.begin ();
        currentr = tweens.rbegin ();
}

/****************************************************************************/

void Timeline::updateRun (int deltaMs, bool direction)
{
        if (direction) {
                (*current)->update (deltaMs, !direction);
        }
        else {
                (*currentr)->update (deltaMs, !direction);
        }
}

/****************************************************************************/

bool Timeline::checkEnd (bool direction)
{
        return (direction && (*current)->getState () == FINISHED && ++current == tweens.end ()) ||
               (!direction && (*currentr)->getState () == INIT && ++currentr == tweens.rend ());

//        ++current;
//        ++currentr;
//        return ((*current)->getState () == END && current == tweens.end ());
}

/****************************************************************************/

IMultiTween *Timeline::add (ITween *tween)
{
        tween->setParent (this);
        tweens.push_back (tween);
        current = tweens.begin ();
        return this;
}

/****************************************************************************/

void Timeline::remove (ITween *tween)
{
        tweens.remove (tween);
        Manager::getMain ()->free (tween);
}

/****************************************************************************/

void Timeline::remove (void const *target, bool onlyActive)
{
        for (TweenList::iterator i = tweens.begin (); i != tweens.end (); ) {
                TweenList::iterator j = i;
                ++j;
                (*i)->remove (target, onlyActive);
                i = j;
        }
}

/****************************************************************************/

void Timeline::remove (void const *target, TweeningProperty *property, bool onlyActive)
{
        for (TweenList::iterator i = tweens.begin (); i != tweens.end ();) {
                TweenList::iterator j = i;
                ++j;
                (*i)->remove (target, property, onlyActive);
                i = j;
        }
}

} /* namespace Tween */
