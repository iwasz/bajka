/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DEBUGCONTROLLER_H_
#define DEBUGCONTROLLER_H_

#include "../controller/IController.h"
#include "ReflectionMacros.h"

namespace Controller {

struct DebugController : public IController {

        C__ (void)
        virtual ~DebugController () {}

        virtual void preUpdate (Model::IModel *m, View::IView *v) {}
        virtual void update (Model::IModel *m, View::IView *v) {}
        virtual void postUpdate (Model::IModel *m, View::IView *v) {}

/*--------------------------------------------------------------------------*/

        virtual bool onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v);

        // linia do dołu
        m_ (setEventMask)
        E_ (DebugController)
};

} /* namespace Controller */

#	endif /* DEBUGCONTROLLER_H_ */
