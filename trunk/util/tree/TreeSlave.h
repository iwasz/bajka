/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TREESLAVE_H_
#define TREESLAVE_H_

#include <algorithm>
#include <cstddef>
#include <boost/functional.hpp>

#include "ITreeSlave.h"

namespace Util {

// Forward
template <typename T>
class TreeMaster;

/**
 * Implementuje interfejs ITreeSlave.
 * \ingroup Tree
 */
template <typename Element>
class TreeSlave : public virtual ITreeSlave <Element> {
public:

        typedef typename ITreeSlave <Element>::ChildBaseType ChildBaseType;
        typedef typename ITreeSlave <Element>::ParentBaseType ParentBaseType;
        typedef typename ITreeSlave <Element>::ChildType ChildType;
        typedef typename ITreeSlave <Element>::ChildConstType ChildConstType;
        typedef typename ITreeSlave <Element>::ParentType ParentType;
        typedef typename ITreeSlave <Element>::ParentConstType ParentConstType;
        typedef typename ITreeSlave <Element>::iterator iterator;
        typedef typename ITreeSlave <Element>::const_iterator const_iterator;
        typedef typename ITreeSlave <Element>::ChildList ChildList;

/*--------------------------------------------------------------------------*/

        TreeSlave () : parent (), children () {}
        virtual ~TreeSlave () {}

/*------IParentAware--------------------------------------------------------*/


        ParentType getParent () { return parent; }
        ParentConstType getParent () const { return parent; }

        ChildList &getChildren () { return children; }
        ChildList const &getChildren () const { return children; }

        /**
         * Iterator do kolekcji dzieci.
         */
        const_iterator begin () const { return children.begin (); }
        iterator begin () { return children.begin (); }

        /**
         * Iterator do kolekcji dzieci.
         */
        const_iterator end () const { return children.end (); }
        iterator end () { return children.end (); }

/*--------------------------------------------------------------------------*/

protected:

        friend class TreeMaster <Element>;

        // Wszystkie poniżej mają być prywatne
        void setParent (ParentType p) { parent = p; }

        /**
         * Kiedy master dodaje dziecko.
         */
        void onAddChild (ChildType e)
        {
                children.push_back (e);
                e->setParent (dynamic_cast <ParentType> (this));
        }

        /**
         * Kiedy master usuwa jedno dziecko.
         */
        void onRemoveChild (ChildType e);

        /**
         * Kiedy master usuwa wszystie dzieci.
         */
        void onClearChildren ();

private:

        ParentType parent;
        ChildList children;
};

/****************************************************************************/

template <typename Element>
void TreeSlave <Element>::onRemoveChild (ChildType e)
{
        typename ChildList::iterator i = std::find (children.begin (), children.end (), e);

        if (i != children.end ()) {
                e->setParent (NULL);
                children.erase (i);
        }
}

/****************************************************************************/

template <typename Element>
void TreeSlave <Element>::onClearChildren ()
{
        std::for_each (children.begin (), children.end (), Util::ConvertPtr <ChildType> (boost::bind2nd (boost::mem_fun (&ChildBaseType::setParent), NULL)));
        children.clear ();
}

}

#	endif /* TREESLAVE_H_ */
