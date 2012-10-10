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

void MultiTween::initExit (bool reverse)
{

}

/****************************************************************************/

void MultiTween::finishedExit (bool reverse)
{

}

/****************************************************************************/

void MultiTween::runEntry (bool reverse)
{

}

/****************************************************************************/

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

} /* namespace Tween */
