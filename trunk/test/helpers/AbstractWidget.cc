/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractWidget.h"
#include "IModel.h"

void AbstractWidget::setModel (Ptr <IModel> m)
{
        model = m;

        if (getParent ()) {
                model->setParent (getParent ()->getModel ().get ());
        }
}

void AbstractWidget::addChild (ChildType e)
{
        Util::TreeMasterSlave <IWidget>::addChild (e);

        if (getModel ()) {
                getModel ()->onAddChild (e->getModel ());
        }
}

void AbstractWidget::removeChild (ChildType e)
{
        Util::TreeMasterSlave <IWidget>::removeChild (e);

        if (getModel ()) {
                getModel ()->onRemoveChild (e->getModel ());
        }
}

void AbstractWidget::clearChildren ()
{
        Util::TreeMasterSlave <IWidget>::clearChildren ();

        if (getModel ()) {
                getModel ()->onClearChildren ();
        }
}

void AbstractWidget::setParent (ParentType p)
{
        Util::TreeMasterSlave <IWidget>::setParent (p);

        if (getModel ()) {
                getModel ()->setParent ((p) ? (p->getModel ().get ()) : (0));
        }
}
