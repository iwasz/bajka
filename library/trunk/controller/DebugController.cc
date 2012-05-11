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

bool DebugController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onButtonPress : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onButtonRelease : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onMouseMotion : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onMouseOver : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onMouseOut : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onKeyDown : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onKeyUp : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onTimer : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onQuit : %x, %s", this, e->toString ().c_str ());
        exit (0);
}

/****************************************************************************/

bool DebugController::onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onActive : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onExpose : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onResize : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onManagerLoad : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

/****************************************************************************/

bool DebugController::onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        LOGI ("DebugController::onManagerUnload : %x, %s", this, e->toString ().c_str ());
        return IGNORED;;
}

} /* namespace Controller */
