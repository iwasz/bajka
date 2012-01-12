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

bool EmptyController::onQuit (Event::QuitEvent *e)
{
        exit (0);
}

} /* namespace Controller */
