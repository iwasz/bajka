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

	timeline ()->add (
                to (testModel, 1000)->
                        rel (SCALE, 4)->
                        rel (ANGLE, 90)->
                        rel (X, 100)->
                        rel (Y, 100)
        )->add (
                to (testModel, 1000)->
                        abs (SCALE, 1)->
                        abs (ANGLE, 0)
        )->start ();

	return Controller::ButtonController::onButtonPress (e, m, v);
}

