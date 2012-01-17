/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "DebugController.h"
#include "types/Types.h"

namespace Controller {

bool DebugController::onButtonPress (Event::ButtonPressEvent *e)
{
        std::cout << e->toString () << std::endl;
}

/****************************************************************************/

bool DebugController::onButtonRelease (Event::ButtonReleaseEvent *e)
{
        std::cout << e->toString () << std::endl;
}

/****************************************************************************/

bool DebugController::onMouseMotion (Event::MouseMotionEvent *e)
{
        std::cout << e->toString () << std::endl;
}

/****************************************************************************/

bool DebugController::onKeyDown (Event::KeyDownEvent *e)
{
        std::cout << e->toString () << std::endl;
}

/****************************************************************************/

bool DebugController::onKeyUp (Event::KeyUpEvent *e)
{
        std::cout << e->toString () << std::endl;
}

/****************************************************************************/

bool DebugController::onTimer (Event::TimerEvent *e)
{
        std::cout << e->toString () << std::endl;
}

/****************************************************************************/

bool DebugController::onQuit (Event::QuitEvent *e)
{
        std::cout << e->toString () << std::endl;
        exit (0);
}

} /* namespace Controller */
