/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITREESLAVE_H_
#define ITREESLAVE_H_

#include "Types.h"

namespace Base {

/**
 * Interfejs dla modeli, które mają dostęp do swoich dzieci i rodziców.
 * Część skałdowa interfejsu IModel (czyli każdy model ma dostęp do struktury
 * drzewiastej modeli).
 *
 * IModel jest oddzielinie, aby zachować jego prostą postać i nie zaciemniać.
 * \inplace Util
 */
struct ITreeModel {

        typedef ModelIter iterator;
        typedef ModelConstIter const_iterator;

        virtual ~ITreeModel () {}

/*------owner / controller / widget-----------------------------------------*/

        virtual ModelOwnerType getOwner () = 0;
        virtual ModelOwnerConstType getOwner () const = 0;
        virtual void setOwner (ModelOwnerType) = 0;

/*------parents-------------------------------------------------------------*/

        virtual ModelParentType getParent () = 0;
        virtual ModelParentConstType getParent () const = 0;

/*------children------------------------------------------------------------*/

        /**
         * Iterator do kolekcji dzieci.
         */
        virtual ModelConstIter begin () const = 0;
        virtual ModelIter begin () = 0;

        /**
         * Iterator do kolekcji dzieci.
         */
        virtual ModelConstIter end () const = 0;
        virtual ModelIter end () = 0;

        /// Są jakieś dzieci.
        virtual bool hasChildren () const = 0;

};

} // namespace

#	endif /* ITREESLAVE_H_ */
