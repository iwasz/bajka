/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITREESLAVE_H_
#define ITREESLAVE_H_

#include "IParentAware.h"

namespace Util {

/**
 * Interfejs dla pobocznej struktury drzewiastej.
 * \ingroup Tree
 */
template <typename Element>
struct ITreeSlave : public virtual IParentAware <Element> {

        typedef typename IParentAware <Element>::ChildBaseType ChildBaseType;
        typedef typename IParentAware <Element>::ParentBaseType ParentBaseType;
        typedef typename IParentAware <Element>::ChildType ChildType;
        typedef typename IParentAware <Element>::ChildConstType ChildConstType;
        typedef typename IParentAware <Element>::ParentType ParentType;
        typedef typename IParentAware <Element>::ParentConstType ParentConstType;
        typedef typename IParentAware <Element>::iterator iterator;
        typedef typename IParentAware <Element>::const_iterator const_iterator;

/*--------------------------------------------------------------------------*/

        virtual ~ITreeSlave () {}

/*--------------------------------------------------------------------------*/

        /**
         * Kiedy master dodaje dziecko.
         */
        virtual void onAddChild (ChildType e) = 0;

        /**
         * Kiedy master usuwa jedno dziecko.
         */
        virtual void onRemoveChild (ChildType e) = 0;

        /**
         * Kiedy master usuwa wszystie dzieci.
         */
        virtual void onClearChildren () = 0;

};

}

#	endif /* ITREESLAVE_H_ */
