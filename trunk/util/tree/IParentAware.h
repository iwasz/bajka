/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IPARENTAWARE_H_
#define IPARENTAWARE_H_

#include <list>
#include "Pointer.h"
#include "Commons.h"

namespace Util {

/**
 * Coś co potrafi zwrócić wskaźnik do rodzica.
 * TODO Zmienić nazę na coś z TREE (ITreeBase?)
 * \ingroup Tree
 */
template <typename Element>
struct IParentAware {

        typedef Element ChildBaseType;
        /// Typ bez żadnych modyfikacji, czyli nie wskaźnik, nie ref, tylko samiuteńki typ.
        typedef Element ParentBaseType;

        /// Typ dzieci. Jest to wskaźnik Ptr do elementu Element.
        typedef Ptr <Element> ChildType;
        // Const musi być po Ptr (a nie po Element), bo kontenery STL też tak definiują robią.
        typedef Ptr <Element> const ChildConstType;

        /// Typ rodzica- zwykły wskaźnik do Element.
        typedef Element *ParentType;
        typedef Element const *ParentConstType;

        typedef typename std::list <ChildType> ChildList;

        typedef typename ChildList::iterator iterator;
        typedef typename ChildList::const_iterator const_iterator;

/*--------------------------------------------------------------------------*/

        virtual ~IParentAware () {}

        virtual ParentType getParent () = 0;
        virtual ParentConstType getParent () const = 0;
        virtual void setParent (ParentType p) = 0;

/*--------------------------------------------------------------------------*/

        virtual ChildList &getChildren () = 0;
        virtual ChildList const &getChildren () const = 0;

        /**
         * Iterator do kolekcji dzieci.
         */
        virtual const_iterator begin () const = 0;
        virtual iterator begin () = 0;

        /**
         * Iterator do kolekcji dzieci.
         */
        virtual const_iterator end () const = 0;
        virtual iterator end () = 0;
};

}

#	endif /* IPARENTAWARE_H_ */
