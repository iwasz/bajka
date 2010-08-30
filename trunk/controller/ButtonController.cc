/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ButtonController.h"

namespace Controller {

void ButtonController::init ()
{
        SimpleController::init ();
        stateful = dynamic_pointer_cast <View::StatefulWidget> (getWidget ());
        ASSERT (stateful, "dynamic_pointer_cast to View::StatefulWidget failed.");
}


bool ButtonController::onMouseOver (Event::MouseMotionEvent *e)
{
        stateful->setCurrentWidget ("hover");
        return true;
}

bool ButtonController::onMouseOut (Event::MouseMotionEvent *e)
{
        stateful->setCurrentWidget ("normal");
        return true;
}

bool ButtonController::onButtonPress (Event::ButtonPressEvent *e)
{
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "clicked" << std::endl;
        stateful->setCurrentWidget ("clicked");
        return true;
}

bool ButtonController::onButtonRelease (Event::ButtonReleaseEvent *e)
{
        stateful->setCurrentWidget ("hover");
        return true;
}

}
