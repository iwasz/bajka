/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BUTTON_CONTROLLER_H_
#define BUTTON_CONTROLLER_H_

#include "SimpleController.h"
#include "CustomRect.h"

/**
 * Kontroler dla wszelkiej maści guzików. Wymaga widgeta typu View::StatefulWidget i
 * modelu typu Model::Shape.
 * \ingroup Kontroler
 */
class CustomController : public Controller::SimpleController {
public:
        __c (void)
        _b ("SimpleController")

        virtual ~CustomController () {}

        /**
         * Metoda inicjująca, którą nalezy uruchomić po ustawieniu wszystich setterów.
         * Widget musi być typu View::StatefulWidget.
         */
        void init ();

        bool onMouseOver (Event::MouseMotionEvent *e);
        bool onMouseOut (Event::MouseMotionEvent *e);

private:

        Ptr <CustomRect> rect;

        _e (CustomController)
};


#       endif /* BUTTON_CONTROLLER_H_ */
