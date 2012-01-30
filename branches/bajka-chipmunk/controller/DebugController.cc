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
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onButtonRelease (Event::ButtonReleaseEvent *e)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onMouseMotion (Event::MouseMotionEvent *e)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onKeyDown (Event::KeyDownEvent *e)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onKeyUp (Event::KeyUpEvent *e)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onTimer (Event::TimerEvent *e)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onQuit (Event::QuitEvent *e)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        exit (0);
}

/****************************************************************************/

bool DebugController::onActive (Event::ActiveEvent *e)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onExpose (Event::ExposeEvent *e)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onResize (Event::ResizeEvent *e)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

} /* namespace Controller */
