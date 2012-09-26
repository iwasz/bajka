/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BUTTON_DO_DIASKA_CONTROLLER_H_
#define BUTTON_DO_DIASKA_CONTROLLER_H_

#include "util/ReflectionMacros.h"
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

/*--------------------------------------------------------------------------*/

        virtual HandlingType onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v);
        virtual HandlingType onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v);
        virtual HandlingType onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        virtual HandlingType onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);

        E_ (ButtonController)
};

} /* namespace Controller */

#	endif /* DEBUGCONTROLLER_H_ */
