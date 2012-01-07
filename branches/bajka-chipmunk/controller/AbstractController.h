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
 * Klasa implementujaca trzon kontrolerów.
 * \ingroup Kontroler
 */
class AbstractController : public TreeController {
public:

        virtual ~AbstractController () {}

        virtual Ptr <View::IWidget> const &getWidget () { return widget; }
        virtual void setWidget (Ptr <View::IWidget> w);

protected:

        AbstractController (Ptr <View::IWidget> w) : widget (w) {}

protected:

        Ptr <View::IWidget> widget;

};

} // nam

#	endif /* ABSTRACTCONTROLLER_H_ */
