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

        HandlingType onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v);
        HandlingType onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v);

        // linia do dołu
        m_ (setEventMask)
        E_ (DebugController)
};

} /* namespace Controller */

#	endif /* DEBUGCONTROLLER_H_ */
