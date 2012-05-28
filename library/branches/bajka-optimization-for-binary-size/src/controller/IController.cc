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

IController::HandlingType IController::onMouseMotionDispatch (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v, Event::PointerInsideIndex *d)
{
        HandlingType ret = IGNORED;

        if (!d->isPointerInside (m)) {
                d->add (m);

                if (eventMask & Event::MOUSE_OVER_EVENT) {
                        ret = onMouseOver (e, m, v);
                }
        }

        if (eventMask & Event::MOUSE_MOTION_EVENT) {
                ret = std::max (onMouseMotion (e, m, v), ret);
        }

        return ret;
}

} /* namespace Controller */
