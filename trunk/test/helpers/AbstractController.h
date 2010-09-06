/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTCONTROLLER_H_
#define ABSTRACTCONTROLLER_H_

#include "IController.h"
#include "tree/TreeMaster.h"
#include <string>

class IWidget;
class IModel;

/**
 *
 */
class AbstractController :
        public IController,
        public Util::TreeMaster <IController> {
public:

        AbstractController (std::string const &s) : name (s) {}
        virtual ~AbstractController () {}

/*------IController---------------------------------------------------------*/

        std::string const &getName () const { return name; }

/*------IModelAware---------------------------------------------------------*/

        Ptr <IModel> getModel () { return model; }
        Ptr <IModel const> getModel () const { return model; }
        void setModel (Ptr <IModel> m);

        Ptr <IWidget> getWidget () { return widget; }
        Ptr <IWidget const> getWidget () const { return widget; }
        void setWidget (Ptr <IWidget> w);

        void addChild (ChildType e);
        void removeChild (ChildType e);
        void clearChildren ();

protected:

        void setParent (ParentType p);

private:

        Ptr <IModel> model;
        Ptr <IWidget> widget;

        std::string name;
};

#	endif /* ABSTRACTCONTROLLER_H_ */
