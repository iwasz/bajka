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

        virtual bool preUpdate (Model::IModel *m, View::IView *v) {}
        virtual bool update (Model::IModel *m, View::IView *v) {}
        virtual bool postUpdate (Model::IModel *m, View::IView *v) {}

/*--------------------------------------------------------------------------*/

        virtual bool onButtonPress (Event::ButtonPressEvent *e) {}
        virtual bool onButtonRelease (Event::ButtonReleaseEvent *e) {}
        virtual bool onMouseMotion (Event::MouseMotionEvent *e) {}
        virtual bool onKeyDown (Event::KeyDownEvent *e) {}
        virtual bool onKeyUp (Event::KeyUpEvent *e) {}
        virtual bool onTimer (Event::TimerEvent *e) {}
        virtual bool onQuit (Event::QuitEvent *e);

        m_ (setEventMask)
        E_ (EmptyController)
};

} /* namespace Controller */

#	endif /* EMPTYCONTROLLER_H_ */
