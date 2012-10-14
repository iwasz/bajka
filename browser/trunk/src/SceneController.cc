/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SceneController.h"
#include "tween/ITween.h"

namespace Tween {

void SceneController::init ()
{
        tweenFactory->create()->start ();
}

SceneController::HandlingType SceneController::onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{

}

} /* namespace Tween */
