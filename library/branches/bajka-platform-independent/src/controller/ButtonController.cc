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

Event::Handling ButtonController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (2);
        return Event::BREAK;
}

/****************************************************************************/

Event::Handling ButtonController::onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (0);
        return Event::BREAK;
}

/****************************************************************************/

Event::Handling ButtonController::onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (1);
        return Event::BREAK;
}

/****************************************************************************/

Event::Handling ButtonController::onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        assertThrow (v, "!v");
        v->setState (0);
        return Event::BREAK;
}

} /* namespace Controller */
