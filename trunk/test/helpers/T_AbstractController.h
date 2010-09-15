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

/**
 *
 */
class T_AbstractController : public Base::TreeController {
public:

        T_AbstractController (std::string const &s) : name (s) {}
        virtual ~T_AbstractController () {}

        Ptr <IWidget> const &getWidget () { return widget; }
        void setWidget (Ptr <IWidget> w)
        {
                widget = w;
                widget->setOwner (this);
        }

/*--------------------------------------------------------------------------*/

        std::string const &getName () const { return name; }

private:

        std::string name;
        Ptr <IWidget> widget;

};

#	endif /* ABSTRACTCONTROLLER_H_ */
