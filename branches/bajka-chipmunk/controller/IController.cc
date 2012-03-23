/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "IController.h"
#include "../events/PointerInsideIndex.h"
#include "../events/types/IEvent.h"

namespace Controller {

bool IController::onMouseMotionDispatch (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v, Event::PointerInsideIndex *d)
{
        if (!d->isPointerInside (m)) {
                d->add (m);

                if (eventMask & Event::MOUSE_OVER_EVENT) {
                        onMouseOver (e, m, v);
                }
        }

        if (eventMask & Event::MOUSE_MOTION_EVENT) {
                onMouseMotion (e, m, v);
        }

        return true;
}

} /* namespace Controller */
