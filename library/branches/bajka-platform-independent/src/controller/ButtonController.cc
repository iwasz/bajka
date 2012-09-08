/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "ButtonController.h"
#include "events/types/Types.h"
#include "view/StatefulWidget.h"
#include "util/Exceptions.h"

using View::StatefulWidget;

namespace Controller {

IController::HandlingType ButtonController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (2);
        return HANDLED;
}

/****************************************************************************/

IController::HandlingType ButtonController::onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (0);
        return HANDLED;
}

/****************************************************************************/

IController::HandlingType ButtonController::onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (1);
        return HANDLED;
}

/****************************************************************************/

IController::HandlingType ButtonController::onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (0);
        return HANDLED;
}

} /* namespace Controller */
