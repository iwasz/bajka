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

        virtual HandlingType onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v);
        virtual HandlingType onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }
        virtual HandlingType onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) { return IGNORED; }

        m_ (setEventMask)
        E_ (EmptyController)
};

} /* namespace Controller */

#	endif /* EMPTYCONTROLLER_H_ */
