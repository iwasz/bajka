/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TweenButtonController.h"
#include "tween/Tween.h"
#include "tween/Manager.h"

using namespace Tween;

Controller::IController::HandlingType TweenButtonController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
	std::cerr << "TweenButtonController::onButtonPress" << std::endl;

//	Geometry::Point p = testModel->getTranslate ();

//	timeline ()->add (
//                to (testModel, 1000, CUBIC_INOUT)->
//                        rel (SCALE, 4)->
//                        rel (ANGLE, 90)->
//                        rel (X, 100)->
//                        rel (Y, 100)->
//                        delay (200)->
//                        repeat (1, true)
//        )->add (
//                to (testModel, 1000)->
//                        abs (SCALE, 0)->
//                        rel (ANGLE, -90)
//        )->start ();

//        from (testModel, 1000, QUART_OUT)->
//                abs (SCALE, 6)->
//                abs (ANGLE, 90)->
//                abs (X, 100)->
//                abs (Y, 100)->
//                delay (200)->
//                repeat (2, true)->
//                start ();

//        timeline ()->add (
//                to (testModel, 1000, BACK_OUT)->
//                        rel (SCALE, 4)->
//                        rel (ANGLE, 90)->
//                        rel (X, 100)->
//                        rel (Y, 100)
//        )->repeat (1, true)->
//        start ();



//        from (testModel, 2000, SINE_INOUT)->
//                abs (X, 100)->
//                abs (Y, 100)->
//                repeat (2, true)->
//                delay (200)->
//                start ();


//        to (testModel, 1000, CUBIC_INOUT)->
//                rel (SCALE, 4)->
//                rel (ANGLE, 90)->
//                rel (X, 100)->
//                rel (Y, 100)->
//                delay (200)->
//                repeat (1, true)->
//                start ();



//        assert (tweenFactory);
//        Tween::ITween *t = tweenFactory->create();
//        Tween::AtomicTween *a = dynamic_cast <Tween::AtomicTween *> (t);
//        a->object = testModel;
//        a->start ();
//

	tweenFactory->create()->start ();
	return DebugButtonController::onButtonPress (e, m, v);
}

