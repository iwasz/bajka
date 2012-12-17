/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include "IController.h"
#include "events/PointerInsideIndex.h"
#include "events/types/IEvent.h"

namespace Controller {

Event::Handling IController::onMotionMoveDispatch (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v, Event::PointerInsideIndex *d)
{
        Event::Handling ret = Event::PASS;

        if (!d->isPointerInside (m)) {
                d->add (m);

                if (eventMask & Event::MOUSE_OVER_EVENT) {
                        ret = onMotionOver (e, m, v);
                }
        }

        if (eventMask & Event::MOTION_MOVE_EVENT) {
                ret = std::max (onMotionMove (e, m, v), ret);
        }

        return ret;
}

} /* namespace Controller */
