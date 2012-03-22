/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EMPTYCONTROLLER_H_
#define EMPTYCONTROLLER_H_

#include "ReflectionMacros.h"
#include "IController.h"

namespace Controller {

struct EmptyController : public IController {

        C__ (void)
        virtual ~EmptyController () {}

        virtual void onPreUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}
        virtual void onUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}
        virtual void onPostUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}

/*--------------------------------------------------------------------------*/

        virtual bool onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) { return true; }
        virtual bool onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) { return true; }

        m_ (setEventMask)
        E_ (EmptyController)
};

} /* namespace Controller */

#	endif /* EMPTYCONTROLLER_H_ */
