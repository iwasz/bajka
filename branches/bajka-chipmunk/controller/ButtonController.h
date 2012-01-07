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
 * \ingroup Kontroler
 */
class ButtonController : public Controller::SimpleController {
public:
        __c (void)
        _b ("SimpleController")

        ButtonController () {}
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

/*--------------------------------------------------------------------------*/

        _m (getSender) Ptr <Signal::Sender> getSender () { return sender; }
        _m (setSender) void setSender (Ptr <Signal::Sender> s) { sender = s; }

private:

        Ptr <View::StatefulWidget> stateful;
        Ptr <Signal::Sender> sender;

        _e (ButtonController)
};

}

#       endif /* BUTTON_CONTROLLER_H_ */
