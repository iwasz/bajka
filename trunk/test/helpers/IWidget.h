/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IWIDGET_H_
#define IWIDGET_H_

#include "tree/ITreeMasterSlave.h"

class IModel;

struct IWidget : public virtual Util::ITreeMasterSlave <IWidget> {

        virtual ~IWidget () {}

        virtual Ptr <IModel> getModel () = 0;
        virtual Ptr <IModel const> getModel () const = 0;
        virtual void setModel (Ptr <IModel> m) = 0;

        virtual std::string const &getName () const = 0;

};

#	endif /* IWIDGET_H_ */
