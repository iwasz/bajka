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

Event::Handling DebugController::onMotionDown (Event::MotionDownEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMotionDown : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onMotionUp (Event::MotionUpEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMotionUp : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onMotionMove (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMotionMove : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onMotionOver (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMotionOver : %p, %s\n", this, e->toString ().c_str ());
        return Event::IGNORE;
}

/****************************************************************************/

Event::Handling DebugController::onMotionOut (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("DebugController::onMotionOut : %p, %s\n", this, e->toString ().c_str ());
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
