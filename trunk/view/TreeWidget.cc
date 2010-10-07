/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include <cstddef>
#include <boost/functional.hpp>
#include <Pointer.h>

#include "TreeWidget.h"
#include "IController.h"

namespace View {
using namespace Base;

void TreeWidget::setModel (Ptr <Model::IModel> m)
{
        model = m;

        if (!model->getOwner () || (!model->getOwner ()->ownsChildren () && ownsChildren ())) {
                model->setOwner (this);
        }

//        if (!model->getOwnerForParent () /*|| (!model->getOwnerForParent ()->getParentMAW () && getParentMAW ())*/) {
                model->setOwnerForParent (this);
//        }
}

/****************************************************************************/

bool TreeWidget::hasChildren () const
{
        return (owner) ? (owner->hasChildren ()) : (!children.empty ());
}

/**
 * Zwraca rodzica lub NULL (a konkretnie WidgetParentType()) jeśli rodzica
 * nie ma. Ta metoda nie sprawdza czy ustawiono ownera, więc jeśli go nie
 * ma, to zachowanie będzie niezdefiniowane. Oczywiście jeśli owner->getParent ()
 * zwraca NULL, to ta metoda także zwraca NULL.
 */
WidgetParentType TreeWidget::getParent ()
{
        if (owner) {
                if (owner->getParent ()) {
                        return owner->getParent ()->getWidget ().get ();
                }

                return WidgetParentType ();
        }

        return parent;
}

/**
 * Zwraca rodzica lub NULL (a konkretnie WidgetParentType()) jeśli rodzica
 * nie ma. Ta metoda nie sprawdza czy ustawiono ownera, więc jeśli go nie
 * ma, to zachowanie będzie niezdefiniowane. Oczywiście jeśli owner->getParent ()
 * zwraca NULL, to ta metoda także zwraca NULL.
 */
WidgetParentConstType TreeWidget::getParent () const
{
        if (owner) {
                if (owner->getParent ()) {
                        return owner->getParent ()->getWidget ().get ();
                }

                return WidgetParentType ();
        }

        return parent;
}

/****************************************************************************/

Model::ModelConstIter TreeWidget::beginForModel () const
{
        return Model::ModelConstIter (children.begin ());
}

/****************************************************************************/

Model::ModelIter TreeWidget::beginForModel ()
{
        return Model::ModelIter (children.begin ());
}

/****************************************************************************/

Model::ModelConstIter TreeWidget::endForModel () const
{
        return Model::ModelConstIter (children.end ());
}

/****************************************************************************/

Model::ModelIter TreeWidget::endForModel ()
{
        return Model::ModelIter (children.end ());
}

/****************************************************************************/
/**
 * Uwaga. W pierwszej kolejności zwracany jest iterator do kolekcji children. Dopiero
 * gdy jest ona pusta, zwracany jest iterator z ownera. Czyli dodając dzieci bezpośrednio
 * do widgetu tracimy dostęp do dzieci kontrolera.
 * @return
 */
WidgetConstIter TreeWidget::begin () const
{
        if (owner && children.empty ()) {
                return const_cast <WidgetOwnerConstType> (owner)->beginForWidget ();
        }

        return WidgetConstIter (children.begin ());
}

/****************************************************************************/

WidgetIter TreeWidget::begin ()
{
        if (owner && children.empty ()) {
                return owner->beginForWidget ();
        }

        return WidgetIter (children.begin ());
}

/****************************************************************************/

WidgetConstIter TreeWidget::end () const
{
        if (owner && children.empty ()) {
                return const_cast <WidgetOwnerConstType> (owner)->endForWidget ();
        }

        return WidgetConstIter (children.end ());
}

/****************************************************************************/

WidgetIter TreeWidget::end ()
{
        if (owner && children.empty ()) {
                return owner->endForWidget ();
        }

        return WidgetIter (children.end ());
}

/****************************************************************************/

void TreeWidget::removeChild (WidgetChildType e)
{
        WidgetCollection::iterator i = std::find (children.begin (), children.end (), e);

        if (i != children.end ()) {
                e->setParent (NULL);
                children.erase (i);
        }
}

/****************************************************************************/

void TreeWidget::clearChildren ()
{
        std::for_each (children.begin (),
                       children.end (),
                       ConvertPtr <WidgetChildType> (boost::bind2nd (boost::mem_fun (&WidgetChildBaseType::setParent), NULL)));

        children.clear ();
}

/****************************************************************************/

void TreeWidget::setChildren (WidgetCollection *col)
{
        clearChildren ();
        addChildren (col);
}

/****************************************************************************/

void TreeWidget::addChildren (WidgetCollection *col)
{
        for (WidgetCollection::iterator i = col->begin (); i != col->end (); ++i) {
                addChild (*i);
        }
}

} // nam
