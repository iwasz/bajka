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
#include "../tween/MultiTween.h"
#include "../tween/Timeline.h"

using namespace Tween;

bool TestButtonController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
	std::cerr << "TestButtonController::onButtonPress" << std::endl;

	MultiTween *mult = new MultiTween;

	{
                AtomicTween *tween = new AtomicTween;
                tween->equation = new Linear;
                tween->accessor = new AngleAccessor;
                tween->durationMs = 3000;
                tween->object = testModel;
                tween->startValue = testModel->getAngle ();
                tween->targetValue = tween->startValue - 200;
                mult->tweens.push_back (tween);
	}

	Timeline *timeline = new Timeline;
        mult->tweens.push_back (timeline);

        {
                AtomicTween *tween = new AtomicTween;
                tween->equation = new Linear;
                tween->accessor = new ScaleAccessor;
                tween->durationMs = 1500;
                tween->object = testModel;
                tween->startValue = 2;
                tween->targetValue = 4;
                timeline->tweens.push_back (tween);
        }

        {
                AtomicTween *tween = new AtomicTween;
                tween->equation = new Linear;
                tween->accessor = new ScaleAccessor;
                tween->durationMs = 1500;
                tween->object = testModel;
                tween->startValue = 4;
                tween->targetValue = 2;
                timeline->tweens.push_back (tween);
        }

        timeline->current =timeline->tweens.begin();
	Manager::getMain ()->setTween (mult);

	return Controller::ButtonController::onButtonPress (e, m, v);
}

