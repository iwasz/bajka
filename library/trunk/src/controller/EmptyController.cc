/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "EmptyController.h"
#include <cstdlib>

namespace Controller {

IController::HandlingType EmptyController::onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v)
{
        exit (0);
        return HANDLED_BREAK;
}

} /* namespace Controller */
