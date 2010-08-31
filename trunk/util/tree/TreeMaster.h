/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TREEMASTER_H_
#define TREEMASTER_H_

#include <Pointer.h>
#include <algorithm>

namespace Util {

/**
 * Interfejs dla głownego drzewa. Patrz dokumentacja od TreeMaster.
 */
template <typename Element>
class ITreeMaster {
public:

        typedef Element ElementType;
        typedef Ptr <Element> ChildType;
        typedef Element *ParentType;
        typedef typename std::vector <ChildType> ElementList;
        typedef typename ElementList::iterator iterator;
        typedef typename ElementList::const_iterator const_iterator;

        virtual ~ITreeMaster () {}

/*------parents-------------------------------------------------------------*/

        virtual ParentType getParent () const = 0;
        virtual void setParent (ParentType p) = 0;

/*------children------------------------------------------------------------*/

        virtual const ElementList &getChildren () const = 0;

        /**
         * Ustawia całą listę dzieci. Ta metoda nie może być szablonem, bo
         * musi być wirtualna.
         */
        virtual void setChildren (const ElementList &e) = 0;

        /**
         * Dodaje listę dzieci do już istniejących .
         */
        virtual void addChildren (const ElementList &e) = 0;

        /**
         * Dodaje dziecko.
         */
        virtual void addChild (ChildType const &e) = 0;

        /**
         * Usuwa dziecko.
         */
        virtual void removeChild (ChildType const &e) = 0;

        /**
         * Usuwa wszystie dzieci.
         */
        virtual void clearChildren () = 0;

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

/**
 * Z tej klasy należy dziedziczyć aby uzyskać funkcjonalność
 * głownego drzewa. Do tego drzewa podłącza się poboczne drzewa,
 * które mją wtedy dostęp do swoich dzieci (swoich typów).
 *
 * TreeMaster ma typ elementu Element i następujące metody:
 * Element *getParent ();
 * std::vector <Ptr <Element> > getChildren ();
 *
 * TreeSlave o elemencie ChildElement zaś wszystko zwraca jako Ptr:
 *
 * Ptr <ChildElement> getParent ();
 * std::vector <Ptr <ChildElement> > getChildren ();
 * \ingroup Tree
 */
template <typename Element>
class TreeMaster : public virtual ITreeMaster <Element> {
public:

        TreeMaster () : parent (0) {}
        virtual ~TreeMaster () {}

/*------parents-------------------------------------------------------------*/

        virtual
        typename ITreeMaster <Element>::ParentType
        getParent () const { return parent; }

/*------children------------------------------------------------------------*/

        virtual
        const typename ITreeMaster <Element>::ElementList &
        getChildren () const { return children; }

        /**
         * Używa addChildren.
         */
        virtual void setChildren (const typename ITreeMaster <Element>::ElementList &e);

        /**
         * Używa addChildren.
         */
        virtual void addChildren (const typename ITreeMaster <Element>::ElementList &e);

        virtual void addChild (typename ITreeMaster <Element>::ChildType const &e)
        {
                children.push_back (e);
                e->setParent (dynamic_cast <typename ITreeMaster <Element>::ParentType> (this));
        }

        virtual void removeChild (const typename ITreeMaster <Element>::ChildType &e) { children.erase (std::find (children.begin (), children.end (), e)); }
        virtual void clearChildren () { children.clear (); }

        typename ITreeMaster <Element>::iterator begin () { return children.begin (); }
        typename ITreeMaster <Element>::const_iterator begin () const { return children.begin (); }

        typename ITreeMaster <Element>::iterator end () { return children.end (); }
        typename ITreeMaster <Element>::const_iterator end () const { return children.end (); }

/*--------------------------------------------------------------------------*/

private:

        void setParent (typename ITreeMaster <Element>::ParentType p) { parent = p; }

private:

        typename ITreeMaster <Element>::ParentType parent;
        typename ITreeMaster <Element>::ElementList children;
};

template <typename Element>
void TreeMaster<Element>::setChildren (const typename ITreeMaster <Element>::ElementList &col)
{
        clearChildren ();
        addChildren (col);
}

template <typename Element>
void TreeMaster<Element>::addChildren (const typename ITreeMaster <Element>::ElementList &col)
{
        for (typename ITreeMaster <Element>::const_iterator i = col.begin (); i != col.end (); ++i) {
                addChild (*i);
        }
}

} // namespace Util

#	endif /* TREEMASTER_H_ */
