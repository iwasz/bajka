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
}

/****************************************************************************/

Timeline *Timeline::add (ITween *tween)
{
        tweens.push_back (tween);
        current = tweens.begin ();
        return this;
}

} /* namespace Tween */
