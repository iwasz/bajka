/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractController.h"
#include "IModel.h"
#include "IWidget.h"

void AbstractController::setModel (Ptr <IModel> m)
{
        model = m;

        if (getParent ()) {
                model->setParent (getParent ()->getModel ().get ());
        }
}

void AbstractController::setWidget (Ptr <IWidget> w)
{
        widget = w;

        if (getParent ()) {
                widget->setParent (getParent ()->getWidget ().get ());
        }
}

void AbstractController::addChild (ChildType e)
{
        Util::TreeMaster <IController>::addChild (e);

        if (getModel ()) {
                getModel ()->onAddChild (e->getModel ());
        }

        if (getWidget ()) {
                getWidget ()->onAddChild (e->getWidget ());
        }
}

void AbstractController::removeChild (ChildType e)
{
        Util::TreeMaster <IController>::removeChild (e);

        if (getModel ()) {
                getModel ()->onRemoveChild (e->getModel ());
        }

        if (getWidget ()) {
                getWidget ()->onRemoveChild (e->getWidget ());
        }
}

void AbstractController::clearChildren ()
{
        Util::TreeMaster <IController>::clearChildren ();

        if (getModel ()) {
                getModel ()->onClearChildren ();
        }

        if (getWidget ()) {
                getWidget ()->onClearChildren ();
        }
}

void AbstractController::setParent (ParentType p)
{
        Util::TreeMaster <IController>::setParent (p);

        if (getModel ()) {
                getModel ()->setParent ((p) ? (p->getModel ().get ()) : (0));
        }

        if (getWidget ()) {
                getWidget ()->setParent ((p) ? (p->getWidget ().get ()) : (0));
        }
}
