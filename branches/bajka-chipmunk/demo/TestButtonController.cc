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
//                        rel (SCALE, 0.5)->
//                        rel (ANGLE, -90)
//        )->start ();

        to (testModel, 1000, CUBIC_INOUT)->
                rel (SCALE, 4)->
                rel (ANGLE, 90)->
                rel (X, 100)->
                rel (Y, 100)->
                delay (200)->
                repeat (1, true)->
                start ();

	return Controller::ButtonController::onButtonPress (e, m, v);
}

