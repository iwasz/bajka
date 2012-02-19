/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TestButtonController.h"
#include "../tween/Tween.h"

using namespace Tween;

bool TestButtonController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
	std::cerr << "TestButtonController::onButtonPress" << std::endl;

	Geometry::Point p = testModel->getTranslate ();

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

        from (testModel, 1000, QUART_OUT)->
                abs (SCALE, 6)->
                abs (ANGLE, 90)->
                abs (X, 100)->
                abs (Y, 100)->
                delay (200)->
                repeat (2, true)->
                start ();

//        timeline ()->add (
//                to (testModel, 1000, BACK_OUT)->
//                        rel (SCALE, 4)->
//                        rel (ANGLE, 90)->
//                        rel (X, 100)->
//                        rel (Y, 100)
//        )->repeat (1, true)->
//        start ();

	return Controller::ButtonController::onButtonPress (e, m, v);
}

