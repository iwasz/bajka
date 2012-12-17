/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DEBUGCONTROLLER_H_
#define DEBUGCONTROLLER_H_

#include "IController.h"
#include "util/ReflectionMacros.h"

namespace Controller {

struct DebugController : public IController {

        C__ (void)
        virtual ~DebugController () {}

        void onPreUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}
        void onUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}
        void onPostUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}

/*--------------------------------------------------------------------------*/

        Event::Handling onMotionDown (Event::MotionDownEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onMotionUp (Event::MotionUpEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onMotionMove (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onMotionOver (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onMotionOut (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v);
        Event::Handling onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v);

        m_ (setEventMask)
        E_ (DebugController)
};

} /* namespace Controller */

#	endif /* DEBUGCONTROLLER_H_ */
