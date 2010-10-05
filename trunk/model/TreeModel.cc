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

Model::ModelConstIter TreeModel::begin () const
{
        return const_cast <Model::IModelAware const *> (owner)->beginForModel ();
}

/****************************************************************************/

Model::ModelIter TreeModel::begin ()
{
        return owner->beginForModel ();
}

/****************************************************************************/

Model::ModelConstIter TreeModel::end () const
{
        return const_cast <Model::IModelAware const *> (owner)->endForModel ();
}

/****************************************************************************/

Model::ModelIter TreeModel::end ()
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
 * nie ma.
 *
 * NIEAKTUALNE - zastanowić się, dlaczego niby miałaby nie sprawdzać. SegF.
 * Bez sprawdzania problematyczne staje się używanie modeli standalone, na
 * przykład w testach.
 *
 * Ta metoda nie sprawdza czy ustawiono ownera, więc jeśli go nie
 * ma, to zachowanie będzie niezdefiniowane. Oczywiście jeśli owner->getParent ()
 * zwraca NULL, to ta metoda także zwraca NULL.
 */
ModelParentType TreeModel::getParent ()
{
        if (owner && owner->getParentMAW ()) {
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
        if (owner && owner->getParentMAW ()) {
                return owner->getParentMAW ()->getModel ().get ();
        }

        return ModelParentConstType ();
}

}
