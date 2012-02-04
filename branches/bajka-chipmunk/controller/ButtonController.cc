/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "ButtonController.h"
#include "types/Types.h"
#include "../view/StatefulWidget.h"
#include "../util/Exceptions.h"

using View::StatefulWidget;

namespace Controller {

bool ButtonController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (2);
        return true;
}

/****************************************************************************/

bool ButtonController::onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (0);
        return true;
}

/****************************************************************************/

bool ButtonController::onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (1);
        return true;
}

/****************************************************************************/

bool ButtonController::onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (0);
        return true;
}

} /* namespace Controller */
