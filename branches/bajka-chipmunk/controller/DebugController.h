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

        virtual bool preUpdate (Model::IModel *m, View::IView *v) {}
        virtual bool update (Model::IModel *m, View::IView *v) {}
        virtual bool postUpdate (Model::IModel *m, View::IView *v) {}

/*--------------------------------------------------------------------------*/

        virtual bool onButtonPress (Event::ButtonPressEvent *e);
        virtual bool onButtonRelease (Event::ButtonReleaseEvent *e);
        virtual bool onMouseMotion (Event::MouseMotionEvent *e);
        virtual bool onKeyDown (Event::KeyDownEvent *e);
        virtual bool onKeyUp (Event::KeyUpEvent *e);
        virtual bool onTimer (Event::TimerEvent *e);
        virtual bool onQuit (Event::QuitEvent *e);
        virtual bool onActive (Event::ActiveEvent *e);
        virtual bool onExpose (Event::ExposeEvent *e);
        virtual bool onResize (Event::ResizeEvent *e);

        // linia do dołu
        m_ (setEventMask)
        E_ (DebugController)
};

} /* namespace Controller */

#	endif /* DEBUGCONTROLLER_H_ */
