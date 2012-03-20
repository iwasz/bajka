/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "IController.h"
#include <iostream>
#include "../events/PointerInsideIndex.h"

namespace Controller {

bool IController::onMouseMotionDispatch (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v, Event::PointerInsideIndex *d)
{
        if (!d->isPointerInside (m)) {
                d->add (m);
                onMouseOver (e, m, v);
        }

        onMouseMotion (e, m, v);
        return true;
}

} /* namespace Controller */
