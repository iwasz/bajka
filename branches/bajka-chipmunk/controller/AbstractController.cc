/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractController.h"

namespace Controller {

void AbstractController::setWidget (Ptr <View::IWidget> w)
{
        widget = w;
        widget->setOwner (this);

        if (widget->getModel ()) {
                setModel (widget->getModel ());
        }
        else if (model) {
                widget->setModel (model);
        }
}

} // nam
