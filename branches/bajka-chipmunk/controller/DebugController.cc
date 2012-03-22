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

bool DebugController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << "DebugController::onMouseOver" << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << "DebugController::onMouseOut" << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        exit (0);
}

/****************************************************************************/

bool DebugController::onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

/****************************************************************************/

bool DebugController::onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        std::cout << std::hex << this << std::dec << " " << e->toString () << std::endl;
        return true;
}

} /* namespace Controller */
