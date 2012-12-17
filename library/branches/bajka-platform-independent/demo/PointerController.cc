/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "PointerController.h"
#include "../model/IModel.h"
#include "../events/types/MouseMotionEvent.h"

namespace Demo {

Event::Handling PointerController::onMouseMotion (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v)
{
        pointer->setTranslate (Geometry::makePoint (e->getPosition ().x + offset.x, e->getPosition ().y + offset.y));
        return Controller::IController::Event::BREAK;
}

} /* namespace Demo */
