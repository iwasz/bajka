/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include <algorithm>
//#include <boost/functional.hpp>
#include <boost/mem_fn.hpp>

#include "AbstractWidget.h"
#include "IModel.h"
#include "Commons.h"

using std::for_each;
//using boost::mem_fun;
//using Util::convertPtr;

namespace View {

// Dla mem_fn - wrzucić do tiliae/Pointer.h
// TODO dlaczego to kurwa nie działa, kiedy jest w Commons.h ?
template <class T>
T *get_pointer (Ptr <T> t)
{
        return t.get ();
}

void AbstractWidget::init ()
{
        for_each (begin (), end (), boost::mem_fn (&IWidget::init));
}

/****************************************************************************/

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
        for_each (begin (), end (), boost::mem_fn (&IWidget::draw));
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
