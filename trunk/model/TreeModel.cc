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
//        if (ownerWgt && ownerWgt->ownsChildren () && !owner->ownsChildren ()) {
////                std::cerr << "TreeModel::begin ()" << std::endl;
//                return const_cast <Model::IModelAware const *> (ownerWgt)->beginForModel ();
//        }
        return const_cast <Model::IModelAware const *> (owner)->beginForModel ();
}

/****************************************************************************/

Model::ModelIter TreeModel::begin ()
{
//        if (ownerWgt && ownerWgt->ownsChildren () && !owner->ownsChildren ()) {
////                std::cerr << "TreeModel::begin ()" << std::endl;
//                return ownerWgt->beginForModel ();
//        }

        return owner->beginForModel ();
}

/****************************************************************************/

Model::ModelConstIter TreeModel::end () const
{
//        if (ownerWgt && ownerWgt->ownsChildren () && !owner->ownsChildren ()) {
//                return const_cast <Model::IModelAware const *> (ownerWgt)->endForModel ();
//        }
        return const_cast <Model::IModelAware const *> (owner)->endForModel ();
}

/****************************************************************************/

Model::ModelIter TreeModel::end ()
{
//        if (ownerWgt && ownerWgt->ownsChildren () && !owner->ownsChildren ()) {
//                return ownerWgt->endForModel ();
//        }
        return owner->endForModel ();
}

/****************************************************************************/

bool TreeModel::hasChildren () const
{
//        if (ownerWgt && ownerWgt->hasChildrenMAW ()) {
//                return true;
//        }

        if (owner) {
                return owner->hasChildrenMAW ();
        }

        return false;
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
#if 1
        std::cerr << (unsigned long int)owner << " "
                  << (unsigned long int)((owner) ? (owner->ownsChildren ()) : 0) << " "
                  << (unsigned long int)ownerForParent << " "
                  << (unsigned long int)((ownerForParent) ? ownerForParent->getParentMAW () : 0) << std::endl;
#endif

//        if (owner && owner->getParentMAW ()) {
//                return owner->getParentMAW ()->getModel ().get ();
//        }

        if (ownerForParent && ownerForParent->getParentMAW ()) {
                return ownerForParent->getParentMAW ()->getModel ().get ();
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
//        if (owner && owner->getParentMAW ()) {
//                return owner->getParentMAW ()->getModel ().get ();
//        }

        if (ownerForParent && ownerForParent->getParentMAW ()) {
                return ownerForParent->getParentMAW ()->getModel ().get ();
        }

        return ModelParentConstType ();
}

}
