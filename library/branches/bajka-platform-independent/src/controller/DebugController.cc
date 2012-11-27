/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Platform.h"
#include "DebugController.h"
#include "events/types/Types.h"

namespace Controller {

IController::IController::HandlingType DebugController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onButtonPress : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onButtonRelease : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMouseMotion : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMouseOver : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMouseOut : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onKeyDown : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onKeyUp : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onTimer : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onQuit : %p, %s\n", this, e->toString ().c_str ());
        exit (0);
}

/****************************************************************************/

IController::HandlingType DebugController::onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onActive : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onExpose : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onResize : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onManagerLoad : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onManagerUnload : %p, %s\n", this, e->toString ().c_str ());
        return IGNORED;
}

} /* namespace Controller */
