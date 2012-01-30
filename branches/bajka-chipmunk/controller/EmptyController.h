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

        virtual void preUpdate (Model::IModel *m, View::IView *v) {}
        virtual void update (Model::IModel *m, View::IView *v) {}
        virtual void postUpdate (Model::IModel *m, View::IView *v) {}

/*--------------------------------------------------------------------------*/

        virtual bool onButtonPress (Event::ButtonPressEvent *e) { return true; }
        virtual bool onButtonRelease (Event::ButtonReleaseEvent *e) { return true; }
        virtual bool onMouseMotion (Event::MouseMotionEvent *e) { return true; }
        virtual bool onKeyDown (Event::KeyDownEvent *e) { return true; }
        virtual bool onKeyUp (Event::KeyUpEvent *e) { return true; }
        virtual bool onTimer (Event::TimerEvent *e) { return true; }
        virtual bool onQuit (Event::QuitEvent *e);
        virtual bool onActive (Event::ActiveEvent *e) { return true; }
        virtual bool onExpose (Event::ExposeEvent *e) { return true; }
        virtual bool onResize (Event::ResizeEvent *e) { return true; }

        m_ (setEventMask)
        E_ (EmptyController)
};

} /* namespace Controller */

#	endif /* EMPTYCONTROLLER_H_ */
