/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TWEEN_BUTTONCONTROLLER_H_
#define TWEEN_BUTTONCONTROLLER_H_

#include "controller/ButtonController.h"

class TweenButtonController : public Controller::ButtonController {
public:

	C__ (void)
	b_ ("ButtonController")

	TweenButtonController () : testModel (NULL) {}
        virtual ~TweenButtonController() {}
        virtual HandlingType onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v);

private:

        Model::IModel *p_ (testModel);

	E_ (TweenButtonController)

};

#endif /* TESTBUTTONCONTROLLER_H_ */
