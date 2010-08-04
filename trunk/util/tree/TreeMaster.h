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

namespace Util {

/**
 * Z tej klasy należy dziedziczyć aby uzyskać funkcjonalność
 * głownego drzewa. Do tego drzewa podłącza się poboczne drzewa,
 * które mją wtedy dostęp do swoich dzieci (swoich typów).
 *
 * Przykład:
 *
 * class Controller : public Util::TreeMaster <Ptr <Controller>, Controller *> {};
 *
 * Wymagania dotyczące typów:
 * - ChildType : Powinien to być jakiś rodzaj smart-pointera.
 * - ParentType : to musi być zwykły wskaźnik.
 */
template <typename ChildType, typename ParentType>
class TreeMaster {
public:

        typedef typename std::vector <ChildType> ElementList;
        typedef typename ElementList::iterator Iterator;

        TreeMaster () : parent (0) {}
        virtual ~TreeMaster () {}

        ParentType getParent () { return parent; }
        ParentType const getParent () const { return parent; }

        const ElementList &getChildren () const { return children; }
        void setChildren (const ElementList &e) { children = e; }

        void addChild (ChildType &e)
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

} // namespace Util

#	endif /* TREEMASTER_H_ */
