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

        void onPreUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}
        void onUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}
        void onPostUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) {}

/*--------------------------------------------------------------------------*/

        bool onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v);
        bool onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v);
        bool onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        bool onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        bool onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        bool onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v);
        bool onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v);
        bool onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v);
        bool onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v);
        bool onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v);
        bool onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v);
        bool onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v);

        // linia do dołu
        m_ (setEventMask)
        E_ (DebugController)
};

} /* namespace Controller */

#	endif /* DEBUGCONTROLLER_H_ */
