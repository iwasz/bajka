/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TWEEN_BUTTONCONTROLLER_H_
#define TWEEN_BUTTONCONTROLLER_H_

#include "tween/parser/ITweenFactory.h"
#include "DebugButtonController.h"

class TweenButtonController : public DebugButtonController {
public:

	C__ (void)
	b_ ("DebugButtonController")

	TweenButtonController () : testModel (NULL) {}
        virtual ~TweenButtonController() {}
        virtual HandlingType onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v);

private:

        Model::IModel           *p_ (testModel);
        Tween::ITweenFactory    *p_ (tweenFactory);

	E_ (TweenButtonController)

};

#endif /* TESTBUTTONCONTROLLER_H_ */
