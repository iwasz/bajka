/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICONTROLLER_H_
#define ICONTROLLER_H_

#include "tree/ITreeMaster.h"
#include "Pointer.h"

class IWidget;
class IModel;

/**
 *
 */
struct IController :
        public virtual Util::ITreeMaster <IController> {

        virtual ~IController () {}

        virtual Ptr <IWidget> getWidget () = 0;
        virtual Ptr <IWidget const> getWidget () const = 0;
        virtual void setWidget (Ptr <IWidget> w) = 0;

        virtual Ptr <IModel> getModel () = 0;
        virtual Ptr <IModel const> getModel () const = 0;
        virtual void setModel (Ptr <IModel> m) = 0;

        virtual std::string const &getName () const = 0;

};

#	endif /* ICONTROLLER_H_ */
