/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTWIDGET_H_
#define ABSTRACTWIDGET_H_

#include <string>

#include "IWidget.h"
#include "Pointer.h"
#include "tree/TreeMasterSlave.h"

class IModel;

/**
 *
 */
class AbstractWidget :
        public IWidget,
        public Util::TreeMasterSlave <IWidget> {
public:

        AbstractWidget (std::string const &s) : name (s) {}
        virtual ~AbstractWidget () {}

/*------IWidget-------------------------------------------------------------*/

        std::string const &getName () const { return name; }

        Ptr <IModel> getModel () { return model; }
        Ptr <IModel const> getModel () const { return model; }
        void setModel (Ptr <IModel> m);

        void addChild (ChildType e);
        void removeChild (ChildType e);
        void clearChildren ();

protected:

        void setParent (ParentType e);

private:

        Ptr <IModel> model;
        std::string name;

};

#	endif /* ABSTRACTWIDGET_H_ */
