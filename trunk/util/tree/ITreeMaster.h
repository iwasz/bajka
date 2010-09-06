/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITREEMASTER_H_
#define ITREEMASTER_H_

#include "IParentAware.h"
#include "Pointer.h"

#include <vector>

namespace Util {

/**
 * Interfejs szkieletu struktury drzewiastej.
 * \ingroup Tree
 */
template <typename Element>
struct  ITreeMaster : public virtual IParentAware <Element> {

        typedef typename IParentAware <Element>::ChildBaseType ChildBaseType;
        typedef typename IParentAware <Element>::ParentBaseType ParentBaseType;
        typedef typename IParentAware <Element>::ChildType ChildType;
        typedef typename IParentAware <Element>::ChildConstType ChildConstType;
        typedef typename IParentAware <Element>::ParentType ParentType;
        typedef typename IParentAware <Element>::ParentConstType ParentConstType;
        typedef typename IParentAware <Element>::iterator iterator;
        typedef typename IParentAware <Element>::const_iterator const_iterator;
        typedef typename IParentAware <Element>::ChildList ChildList;

/*--------------------------------------------------------------------------*/

        virtual ~ITreeMaster () {}

/*------children------------------------------------------------------------*/

        /**
         * Ustawia całą listę dzieci. Ta metoda nie może być szablonem, bo
         * musi być wirtualna. Modyfikuje podaną listę (ustawia dzieciom parenty
         * na siebie).
         */
        virtual void setChildren (ChildList *e) = 0;

        /**
         * Dodaje listę dzieci do już istniejących .
         */
        virtual void addChildren (ChildList *e) = 0;

        /**
         * Dodaje dziecko.
         */
        virtual void addChild (ChildType e) = 0;

        /**
         * Usuwa dziecko.
         */
        virtual void removeChild (ChildType e) = 0;

        /**
         * Usuwa wszystie dzieci.
         */
        virtual void clearChildren () = 0;


};

}

#	endif /* ITREEMASTER_H_ */
