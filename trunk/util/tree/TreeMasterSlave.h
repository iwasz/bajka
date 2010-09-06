/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TREEMASTERSLAVE_H_
#define TREEMASTERSLAVE_H_

#include <algorithm>
#include <cstddef>
#include <boost/functional.hpp>

#include "ITreeMasterSlave.h"

namespace Util {

/**
 * Łączy w sobie i TreeSlave i TreeMaster, to znaczy można dodawać do niego
 * dzieci bezpośrednio, a można też dodawać dzieci do jego Mastera.
 * \ingroup Tree
 */
template <typename Element>
class TreeMasterSlave :
        public virtual ITreeMasterSlave <Element> {

public:

        // Odpowiadające typy z ITreeMaster są takie same.
        typedef typename ITreeSlave <Element>::ChildBaseType ChildBaseType;
        typedef typename ITreeSlave <Element>::ParentBaseType ParentBaseType;
        typedef typename ITreeSlave <Element>::ChildType ChildType;
        typedef typename ITreeSlave <Element>::ChildConstType ChildConstType;
        typedef typename ITreeSlave <Element>::ParentType ParentType;
        typedef typename ITreeSlave <Element>::ParentConstType ParentConstType;
        typedef typename ITreeSlave <Element>::iterator iterator;
        typedef typename ITreeSlave <Element>::const_iterator const_iterator;
        typedef typename ITreeSlave <Element>::ChildList ChildList;

        TreeMasterSlave () : parent (), children () {}
        virtual ~TreeMasterSlave () {}

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

/*------ITreeMaster---------------------------------------------------------*/

        /**
         * Ustawia całą listę dzieci. Używa addChild.
         */
        void setChildren (ChildList *e);

        /**
         * Dodaje listę dzieci do już istniejących. Używa addChild.
         */
        void addChildren (ChildList *e);

        /**
         * Dodaje dziecko.
         */
        virtual void addChild (ChildType e)
        {
                children.push_back (e);
                e->setParent (dynamic_cast <ParentType> (this));
        }

        /**
         * Usuwa pierwsze dziecko o wartości równej e. Ustawia mu także parent na NULL.
         */
        void removeChild (ChildType e);

        /**
         * Czyści listę dzieci. Ustawia wszystkim parent na NULL.
         */
        void clearChildren ();

protected:

        void setParent (ParentType p) { parent = p; }

        void onAddChild (ChildType e) { addChild (e); }

        /**
         * Kiedy master usuwa jedno dziecko.
         */
        void onRemoveChild (ChildType e) { removeChild (e); }

        /**
         * Kiedy master usuwa wszystie dzieci.
         */
        void onClearChildren () { clearChildren (); }

private:

        ParentType parent;
        ChildList children;

};

/****************************************************************************/

template <typename Element>
void TreeMasterSlave <Element>::removeChild (ChildType e)
{
        typename ChildList::iterator i = std::find (children.begin (), children.end (), e);

        if (i != children.end ()) {
                e->setParent (NULL);
                children.erase (i);
        }
}

/****************************************************************************/

template <typename Element>
void TreeMasterSlave <Element>::clearChildren ()
{
        std::for_each (children.begin (), children.end (), Util::ConvertPtr <ChildType> (boost::bind2nd (boost::mem_fun (&ChildBaseType::setParent), NULL)));
        children.clear ();
}

/****************************************************************************/

template <typename Element>
void TreeMasterSlave <Element>::setChildren (ChildList *col)
{
        clearChildren ();
        addChildren (col);
}

/****************************************************************************/

template <typename Element>
void TreeMasterSlave <Element>::addChildren (ChildList *col)
{
        for (typename ChildList::iterator i = col->begin (); i != col->end (); ++i) {
                addChild (*i);
        }
}

}

#	endif /* TREEMASTERSLAVE_H_ */
