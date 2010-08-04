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
 */
template <typename Element>
class TreeMaster {
public:

        typedef Element ElementType;
        typedef Ptr <Element> ChildType;
        typedef Element *ParentType;
        typedef typename std::vector <ChildType> ElementList;
        typedef typename ElementList::iterator Iterator;

        TreeMaster () : parent (0) {}
        virtual ~TreeMaster () {}

        ParentType getParent () { return parent; }
        ParentType const getParent () const { return parent; }

        const ElementList &getChildren () const { return children; }
        void setChildren (const ElementList &e) { children = e; }

        void addChild (ChildType e)
        {
                children.push_back (e);
                e->setParent (dynamic_cast <ParentType> (this));
        }

        void removeChild (const ChildType &e) { children.erase (std::find (children.begin (), children.end (), e)); }
        void clearChildren () { children.clear (); }

        Iterator begin () { return children.begin (); }
        Iterator end () { return children.end (); }

private:

        void setParent (ParentType p) { parent = p; }

private:

        ParentType parent;
        ElementList children;
};


template <typename Element>
class ITreeMaster {
public:

        typedef Element ElementType;
        typedef Ptr <Element> ChildType;
        typedef Element *ParentType;
        typedef typename std::vector <ChildType> ElementList;
        typedef typename ElementList::iterator Iterator;

        virtual ~ITreeMaster () {}

        virtual ParentType getParent () = 0;
        virtual ParentType const getParent () const = 0;

        virtual const ElementList &getChildren () const = 0;
        virtual void setChildren (const ElementList &e) = 0;
        virtual void addChild (ChildType e) = 0;
        virtual void removeChild (const ChildType &e) = 0;
        virtual void clearChildren () = 0;

        virtual Iterator begin () = 0;
        virtual Iterator end () = 0;

};
} // namespace Util

#	endif /* TREEMASTER_H_ */
