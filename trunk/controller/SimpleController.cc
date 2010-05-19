/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Foreach.h>
#include "SimpleController.h"

namespace Controller {

void SimpleController::init ()
{
        foreach (Ptr <IController> child, children) {
                child->init ();
        }

        if (widget) {
                widget->init ();
        }
}

/****************************************************************************/

void SimpleController::draw ()
{
        // If render is set to false, we skip drawing this Widget.
        if (!getRender ()) {
                return;
        }

        if (widget) {
                widget->preDraw ();
                widget->draw ();
        }

        doChildren ();

        if (widget) {
                widget->postDraw ();
        }
}

void SimpleController::doChildren ()
{
        foreach (Ptr <IController> child, children) {
                child->draw ();
        }
}

/****************************************************************************/

void SimpleController::onEvent (const Event::IEvent &event)
{
        static int i = 0;
        std::cerr << "onEvent : " << i++ << ", type : " << event.getType() << std::endl;
}

}
