/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BUTTON_CONTROLLER_H_
#define BUTTON_CONTROLLER_H_

#include <Signal.h>
#include "SimpleController.h"
#include "../view/StatefulWidget.h"

namespace Controller {

/**
 * Kontroler dla wszelkiej maści guzików. Wymaga widgeta typu View::StatefulWidget i
 * modelu typu Model::Shape.
 */
class ButtonController : public Controller::SimpleController {
public:
        __c (void)
        _b ("SimpleController")

        ButtonController () : sender (this) {}
        virtual ~ButtonController () {}

        /**
         * Metoda inicjująca, którą nalezy uruchomić po ustawieniu wszystich setterów.
         * Widget musi być typu View::StatefulWidget.
         */
        virtual void init ();

        virtual bool onMouseOver (Event::MouseMotionEvent *e);
        virtual bool onMouseOut (Event::MouseMotionEvent *e);
        virtual bool onButtonPress (Event::ButtonPressEvent *e);
        virtual bool onButtonRelease (Event::ButtonReleaseEvent *e);

private:

        Signal::Sender sender;
        Ptr <View::StatefulWidget> stateful;

        _e (ButtonController)
};

}

#       endif /* BUTTON_CONTROLLER_H_ */
