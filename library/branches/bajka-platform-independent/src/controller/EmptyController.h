/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EMPTYCONTROLLER_H_
#define EMPTYCONTROLLER_H_

#include "util/ReflectionMacros.h"
#include "IController.h"

namespace Controller {

struct EmptyController : public IController {

        C__ (void)
        virtual ~EmptyController () {}

        virtual void onPreUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}
        virtual void onUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}
        virtual void onPostUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}

/*--------------------------------------------------------------------------*/

        virtual Event::Handling onMotionDown (Event::MotionDownEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }
        virtual Event::Handling onMotionUp (Event::MotionUpEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }
        virtual Event::Handling onMotionMove (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }
        virtual Event::Handling onMotionOver (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }
        virtual Event::Handling onMotionOut (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }
        virtual Event::Handling onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }
        virtual Event::Handling onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }
        virtual Event::Handling onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }
        virtual Event::Handling onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }
        virtual Event::Handling onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }
        virtual Event::Handling onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) { return Event::IGNORE; }

        m_ (setEventMask)
        E_ (EmptyController)
};

} /* namespace Controller */

#	endif /* EMPTYCONTROLLER_H_ */
