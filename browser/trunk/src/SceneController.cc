/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SceneController.h"

namespace Tween {

void SceneController::init ()
{
        tweenFactory->create()->start ();
}

} /* namespace Tween */
