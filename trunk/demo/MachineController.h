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
#include "CustomRect.h"

/**
 * Kontroler dla wszelkiej maści guzików. Wymaga widgeta typu View::StatefulWidget i
 * modelu typu Model::Shape.
 * \ingroup Kontroler
 */
class MachineController : public Controller::SimpleController {
public:
        __c (void)
        _b ("SimpleController")

        MachineController () : onButton (this, "/toolbox/clicked", "$clicked ()") {}
        virtual ~MachineController () {}
        void init ();
        _m (clicked) void clicked ();

private:

        Signal::Listener onButton;
        Ptr <CustomRect> rect;

        _e (MachineController)
};


#       endif /* BUTTON_CONTROLLER_H_ */
