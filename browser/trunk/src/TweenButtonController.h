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

	TweenButtonController () : tweenFactory (NULL) {}
        virtual ~TweenButtonController() {}
        virtual Event::Handling onButtonPress (Event::MotionDownEvent *e, Model::IModel *m, View::IView *v);

private:

        Tween::ITweenFactory    *p_ (tweenFactory);

	E_ (TweenButtonController)

};

#endif /* TESTBUTTONCONTROLLER_H_ */
