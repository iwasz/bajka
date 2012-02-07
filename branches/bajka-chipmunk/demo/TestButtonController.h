/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TESTBUTTONCONTROLLER_H_
#define TESTBUTTONCONTROLLER_H_

#include "../controller/ButtonController.h"

class TestButtonController : public Controller::ButtonController {
public:

	C__ (void)
	b_ ("ButtonController")

	virtual ~TestButtonController() {}
    virtual bool onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v);

    S_ (setTestModel) void setTestModel (Model::IModel *m) { testModel = m; }

private:

    Model::IModel *testModel;

	E_ (TestButtonController)

};

#endif /* TESTBUTTONCONTROLLER_H_ */
