/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DEBUGCONTROLLER_H_
#define DEBUGCONTROLLER_H_

#include "ReflectionMacros.h"
#include "EmptyController.h"

namespace Controller {

/**
 * Zmienia stan widoku w zależności od eventu:
 * - 0 : normalny stan.
 * - 1 : hover.
 * - 2 : clicked.
 */
struct ButtonController : public EmptyController {

        C__ (void)
        b_ ("EmptyController")
        virtual ~ButtonController () {}

        virtual void preUpdate (Model::IModel *m, View::IView *v) {}
        virtual void update (Model::IModel *m, View::IView *v) {}
        virtual void postUpdate (Model::IModel *m, View::IView *v) {}

/*--------------------------------------------------------------------------*/

        virtual bool onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        virtual bool onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);

        E_ (ButtonController)
};

} /* namespace Controller */

#	endif /* DEBUGCONTROLLER_H_ */
