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

Event::Handling DebugController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onButtonPress : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onButtonRelease : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMouseMotion : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMouseOver : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMouseOut : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onKeyDown : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onKeyUp : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onQuit : %p, %s\n", this, e->toString ().c_str ());
        exit (0);
}

/****************************************************************************/

Event::Handling DebugController::onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onResize : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onManagerLoad : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onManagerUnload : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

} /* namespace Controller */
