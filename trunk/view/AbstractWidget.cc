/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>

#include "AbstractWidget.h"
#include "IModel.h"

namespace View {

void AbstractWidget::preDraw ()
{
        glPushMatrix ();
}

/****************************************************************************/

void AbstractWidget::doTransform ()
{
        if (model) {
                glMultMatrixd (model->getMatrix ().data ().begin ());
        }
}

/****************************************************************************/

void AbstractWidget::doChildren ()
{
        for (AbstractWidget::iterator i = begin (); i != end (); ++i) {
                (*i)->draw ();
        }
}

/****************************************************************************/

void AbstractWidget::postDraw ()
{
        glPopMatrix ();
}

/****************************************************************************/

void AbstractWidget::draw ()
{
        // If render is set to false, we skip drawing this Widget.
        if (!visible) {
                return;
        }

        preDraw ();
        doTransform ();
        doDraw ();
        doChildren ();
        postDraw ();
}

/*##########################################################################*/

void AbstractWidget::setModel (Ptr <Model::IModel> m)
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

void AbstractWidget::setChildren (WidgetList const &list)
{
        for (WidgetList::const_iterator i = list.begin (); i !=list.end (); ++i) {
                addChild (*i);
        }
}

}
