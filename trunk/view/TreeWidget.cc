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

ModelConstIter TreeWidget::beginForModel () const
{
        return ModelConstIter (children.begin ());
}

/****************************************************************************/

ModelIter TreeWidget::beginForModel ()
{
        return ModelIter (children.begin ());
}

/****************************************************************************/

ModelConstIter TreeWidget::endForModel () const
{
        return ModelConstIter (children.end ());
}

/****************************************************************************/

ModelIter TreeWidget::endForModel ()
{
        return ModelIter (children.end ());
}

/****************************************************************************/

WidgetConstIter TreeWidget::begin () const
{
        if (owner) {
                return const_cast <WidgetOwnerConstType> (owner)->beginForWidget ();
        }

        return WidgetConstIter (children.begin ());
}

/****************************************************************************/

WidgetIter TreeWidget::begin ()
{
        if (owner) {
                return owner->beginForWidget ();
        }

        return WidgetIter (children.begin ());
}

/****************************************************************************/

WidgetConstIter TreeWidget::end () const
{
        if (owner) {
                return const_cast <WidgetOwnerConstType> (owner)->endForWidget ();
        }

        return WidgetConstIter (children.end ());
}

/****************************************************************************/

WidgetIter TreeWidget::end ()
{
        if (owner) {
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
