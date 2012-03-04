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

bool PointerController::onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        pointer->setTranslate (e->getPosition ());
//        std::cerr << e->getPosition () << std::endl;
        return true;
}

} /* namespace Demo */
