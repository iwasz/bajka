/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTCONTROLLER_H_
#define ABSTRACTCONTROLLER_H_

#include "TreeController.h"

namespace Controller {

/**
 *
 */
class AbstractController : public TreeController {
public:

        virtual ~AbstractController () {}

        Ptr <View::IWidget> const &getWidget () { return widget; }
        void setWidget (Ptr <View::IWidget> w)
        {
                widget = w;
                widget->setOwner (this);
        }

protected:

        AbstractController (Ptr <View::IWidget> w) : widget (w) {}

protected:

        Ptr <View::IWidget> widget;

};

} // nam

#	endif /* ABSTRACTCONTROLLER_H_ */
