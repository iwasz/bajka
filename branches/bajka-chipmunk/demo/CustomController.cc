/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "CustomController.h"

void CustomController::init ()
{
        SimpleController::init ();
        rect = dynamic_pointer_cast <CustomRect> (getWidget ());
        ASSERT (rect , "dynamic_pointer_cast to View::StatefulWidget failed.");
}

bool CustomController::onMouseOver (Event::MouseMotionEvent *e)
{
        rect->setFill (true);
        return true;
}

bool CustomController::onMouseOut (Event::MouseMotionEvent *e)
{
        rect->setFill (false);
        return true;
}

