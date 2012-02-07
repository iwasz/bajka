/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TestButtonController.h"
#include "../tween/AtomicTween.h"
#include "../tween/ease/Linear.h"
#include "../tween/accessor/AffineAccessor.h"
#include "../tween/Manager.h"

using namespace Tween;

bool TestButtonController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
	std::cerr << "TestButtonController::onButtonPress" << std::endl;

	AtomicTween *tween = new AtomicTween;
	tween->equation = new Linear;
	tween->accessor = new AngleAccessor;
	tween->durationMs = 3000;
	tween->object = testModel;
	tween->startValue = testModel->getAngle ();
	tween->targetValue = tween->startValue - 200;
	Manager::getMain ()->setTween (tween);

	return Controller::ButtonController::onButtonPress (e, m, v);
}

