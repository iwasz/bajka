/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TreeModel.h"

namespace Model {
using namespace Base;

Base::ModelConstIter TreeModel::begin () const
{
        return const_cast <Base::IModelAware const *> (owner)->beginForModel ();
}

/****************************************************************************/

Base::ModelIter TreeModel::begin ()
{
        return owner->beginForModel ();
}

/****************************************************************************/

Base::ModelConstIter TreeModel::end () const
{
        return const_cast <Base::IModelAware const *> (owner)->endForModel ();
}

/****************************************************************************/

Base::ModelIter TreeModel::end ()
{
        return owner->endForModel ();
}

/****************************************************************************/

bool TreeModel::hasChildren () const
{
        return (owner) ? (owner->hasChildrenMAW ()) : (true);
}

/**
 * Zwraca rodzica lub NULL (a konkretnie ModelParentType()) jeśli rodzica
 * nie ma. Ta metoda nie sprawdza czy ustawiono ownera, więc jeśli go nie
 * ma, to zachowanie będzie niezdefiniowane. Oczywiście jeśli owner->getParent ()
 * zwraca NULL, to ta metoda także zwraca NULL.
 */
ModelParentType TreeModel::getParent ()
{
        if (owner->getParentMAW ()) {
                return owner->getParentMAW ()->getModel ().get ();
        }

        return ModelParentType ();
}

/**
 * Zwraca rodzica lub NULL (a konkretnie ModelParentType()) jeśli rodzica
 * nie ma. Ta metoda nie sprawdza czy ustawiono ownera, więc jeśli go nie
 * ma, to zachowanie będzie niezdefiniowane. Oczywiście jeśli owner->getParent ()
 * zwraca NULL, to ta metoda także zwraca NULL.
 */
ModelParentConstType TreeModel::getParent () const
{
        if (owner->getParentMAW ()) {
                return owner->getParentMAW ()->getModel ().get ();
        }

        return ModelParentConstType ();
}

}
