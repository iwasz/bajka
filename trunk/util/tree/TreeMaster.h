/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TREEMASTER_H_
#define TREEMASTER_H_

#include <algorithm>
#include <cstddef>
#include <boost/functional.hpp>
#include <boost/mem_fn.hpp>

#include "ITreeMaster.h"
#include "Commons.h"

namespace Util {

/**
 * Implementacja ITreeMaster.
 * \ingroup Tree
 */
template <typename Element>
class TreeMaster : public virtual ITreeMaster <Element> {
public:

        typedef typename ITreeMaster <Element>::ChildBaseType ChildBaseType;
        typedef typename ITreeMaster <Element>::ParentBaseType ParentBaseType;
        typedef typename ITreeMaster <Element>::ChildType ChildType;
        typedef typename ITreeMaster <Element>::ChildConstType ChildConstType;
        typedef typename ITreeMaster <Element>::ParentType ParentType;
        typedef typename ITreeMaster <Element>::ParentConstType ParentConstType;
        typedef typename ITreeMaster <Element>::iterator iterator;
        typedef typename ITreeMaster <Element>::const_iterator const_iterator;
        typedef typename ITreeMaster <Element>::ChildList ChildList;

/*--------------------------------------------------------------------------*/

        TreeMaster () : parent (), children () {}
        virtual ~TreeMaster () {}

/*------IParentEnabled------------------------------------------------------*/

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
         * Tu trzeba dodać odwołania do slave-ów.
         */
        virtual void addChild (ChildType e)
        {
                children.push_back (e);
                e->setParent (dynamic_cast <ParentType> (this));
        }

        /**
         * Usuwa pierwsze dziecko o wartości równej e. Ustawia mu także parent na NULL.
         * Tu trzeba dodać odwołania do slave-ów.
         */
        virtual void removeChild (ChildType e);

        /**
         * Czyści listę dzieci. Ustawia wszystkim parent na NULL.
         * Tu trzeba dodać odwołania do slave-ów.
         */
        virtual void clearChildren ();

protected:

        virtual void setParent (ParentType p) { parent = p; }

private:

        ParentType parent;
        ChildList children;

};

/****************************************************************************/

template <typename Element>
void TreeMaster <Element>::removeChild (ChildType e)
{
        typename ChildList::iterator i = std::find (children.begin (), children.end (), e);

        if (i != children.end ()) {
                e->setParent (NULL);
                children.erase (i);
        }
}

/****************************************************************************/

template <typename Element>
void TreeMaster <Element>::clearChildren ()
{
        std::for_each (children.begin (), children.end (), Util::convertPtr <ChildType> (boost::bind2nd (boost::mem_fun (&ChildBaseType::setParent), NULL)));
        children.clear ();
}

/****************************************************************************/

template <typename Element>
void TreeMaster <Element>::setChildren (ChildList *col)
{
        clearChildren ();
        addChildren (col);
}

/****************************************************************************/

template <typename Element>
void TreeMaster <Element>::addChildren (ChildList *col)
{
        for (typename ChildList::iterator i = col->begin (); i != col->end (); ++i) {
                addChild (*i);
        }
}

}

#	endif /* TREEMASTER_H_ */
