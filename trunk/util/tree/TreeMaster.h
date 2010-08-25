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
class TreeMaster {
public:

        typedef Element ElementType;
        typedef Ptr <Element> ChildType;
        typedef Element *ParentType;
        typedef typename std::vector <ChildType> ElementList;
        typedef typename ElementList::const_iterator Iterator;

        TreeMaster () : parent (0) {}
        virtual ~TreeMaster () {}

/*------parents-------------------------------------------------------------*/

        virtual ParentType getParent () { return parent; }
        virtual ParentType const getParent () const { return parent; }

/*------children------------------------------------------------------------*/

        virtual const ElementList &getChildren () const { return children; }

        /**
         * Wszytkie poniższe metody dodające w końcu używają addChildren.
         */
        template <typename Collection>
        void setChildren (const Collection &e);

        template <typename Collection>
        void addChildren (const Collection &e);

        template <typename Iter>
        void setChildren (Iter const &b, Iter const &e);

        template <typename Iter>
        void addChildren (Iter const &b, Iter const &e);

        virtual void addChild (ChildType e)
        {
                children.push_back (e);
                e->setParent (dynamic_cast <ParentType> (this));
        }

        virtual void removeChild (const ChildType &e) { children.erase (std::find (children.begin (), children.end (), e)); }
        virtual void clearChildren () { children.clear (); }

        Iterator begin () const { return children.begin (); }
        Iterator end () const { return children.end (); }

/*--------------------------------------------------------------------------*/

private:

        void setParent (ParentType p) { parent = p; }

private:

        ParentType parent;
        ElementList children;
};

template <typename Element>
template <typename Collection>
void TreeMaster<Element>::setChildren (const Collection &col)
{
        setChildren (col.begin (), col.end ());
}

template <typename Element>
template <typename Collection>
void TreeMaster<Element>::addChildren (const Collection &col)
{
        addChildren (col.begin (), col.end ());
}

/*
 * Nie używam std::copy, ponieważ addChild ustawia parenta.
 */
template <typename Element>
template <typename Iter>
void TreeMaster<Element>::setChildren (Iter const &b, Iter const &e)
{
        clearChildren ();
        addChildren (b, e);
}

/*
 *
 */
template <typename Element>
template <typename Iter>
void TreeMaster<Element>::addChildren (Iter const &b, Iter const &e)
{
        for (Iter i = b; i != e; ++i) {
                addChild (*i);
        }
}

//template <typename Element>
//class ITreeMaster {
//public:
//
//        typedef Element ElementType;
//        typedef Ptr <Element> ChildType;
//        typedef Element *ParentType;
//        typedef typename std::vector <ChildType> ElementList;
//        typedef typename ElementList::iterator Iterator;
//
//        virtual ~ITreeMaster () {}
//
//        virtual ParentType getParent () = 0;
//        virtual ParentType const getParent () const = 0;
//
//        virtual const ElementList &getChildren () const = 0;
//        virtual void setChildren (const ElementList &e) = 0;
//        virtual void addChild (ChildType e) = 0;
//        virtual void removeChild (const ChildType &e) = 0;
//        virtual void clearChildren () = 0;
//
//        virtual Iterator begin () = 0;
//        virtual Iterator end () = 0;
//
//};

} // namespace Util

#	endif /* TREEMASTER_H_ */
