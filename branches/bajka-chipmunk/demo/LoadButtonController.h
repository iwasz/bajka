/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LOAD_BUTTONCONTROLLER_H_
#define LOAD_BUTTONCONTROLLER_H_

#include "../controller/ButtonController.h"
#include "../util/App.h"

class LoadButtonController : public Controller::ButtonController {
public:

	C__ (void)
	b_ ("ButtonController")

        virtual ~LoadButtonController() {}
        virtual bool onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
        {
                manager ()->play (name);
                return false;
        }

        m_ (setName) void setName (std::string const &s) { name = s; }

private:

        std::string name;

	E_ (LoadButtonController)

};

#endif /* TESTBUTTONCONTROLLER_H_ */
