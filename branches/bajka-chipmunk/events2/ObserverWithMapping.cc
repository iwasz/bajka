/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ObserverWithMapping.h"
#include "../controller/mapping/IMapping.h"

namespace Event {

bool ObserverWithMapping::onButtonPress (ButtonPressEvent *)
{
        mapping->run ();
        return true;
}

bool ObserverWithMapping::onButtonRelease (ButtonReleaseEvent *)
{
        mapping->run ();
        return true;
}

bool ObserverWithMapping::onMouseMotion (MouseMotionEvent *)
{
        mapping->run ();
        return true;
}

bool ObserverWithMapping::onKeyDown (KeyDownEvent *)
{
        mapping->run ();
        return true;
}

bool ObserverWithMapping::onKeyUp (KeyUpEvent *)
{
        mapping->run ();
        return true;
}

bool ObserverWithMapping::onTimer (TimerEvent *)
{
        mapping->run ();
        return true;
}

bool ObserverWithMapping::onQuit (QuitEvent *)
{
        mapping->run ();
        return true;
}

}
