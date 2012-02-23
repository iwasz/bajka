/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "IController.h"
#include <iostream>
#include "../events/IDispatcher.h"

namespace Controller {

bool IController::onMouseMotionDispatch (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v, Event::IDispatcher *d)
{
        if (!d->isPointerInside (m)) {
                d->setPointerInside (m);
                onMouseOver (e, m, v);
        }

        onMouseMotion (e, m, v);
        return true;
}

} /* namespace Controller */
