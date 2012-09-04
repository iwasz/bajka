/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Logging.h"
#include "DebugController.h"
#include "types/Types.h"

namespace Controller {

IController::IController::HandlingType DebugController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onButtonPress : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onButtonRelease : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onMouseMotion : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onMouseOver : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onMouseOut : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onKeyDown : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onKeyUp : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onTimer : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onQuit : %p, %s", this, e->toString ().c_str ());
        exit (0);
}

/****************************************************************************/

IController::HandlingType DebugController::onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onActive : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onExpose : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onResize : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onManagerLoad : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

/****************************************************************************/

IController::HandlingType DebugController::onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onManagerUnload : %p, %s", this, e->toString ().c_str ());
        return IGNORED;
}

} /* namespace Controller */
