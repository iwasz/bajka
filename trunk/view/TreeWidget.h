/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TREEWIDGET_H_
#define TREEWIDGET_H_

#include "IWidget.h"
#include "IModel.h"
#include "../base/tree/Types.h"

namespace View {

/**
 *
 */
struct TreeWidget : public IWidget {

        typedef Base::WidgetIter iterator;
        typedef Base::WidgetConstIter const_iterator;

        TreeWidget () : children (), parent (), model (), owner () {}
        virtual ~TreeWidget () {}

/*------IModelAware---------------------------------------------------------*/

        Ptr <Model::IModel> const &getModel () { return model; }
        void setModel (Ptr <Model::IModel> m);

        Base::IModelAware *getParentMAW () { return parent; }
        bool hasChildrenMAW () const { return hasChildren (); }

/*------parents-------------------------------------------------------------*/

        Base::WidgetParentType getParent ();
        Base::WidgetParentConstType getParent () const;
        void setParent (Base::WidgetParentType p) { parent = p; }

/*------children------------------------------------------------------------*/

        Base::WidgetConstIter begin () const;
        Base::WidgetIter begin ();
        Base::WidgetConstIter end () const;
        Base::WidgetIter end ();

        Base::ModelConstIter beginForModel () const;
        Base::ModelIter beginForModel ();
        Base::ModelConstIter endForModel () const;
        Base::ModelIter endForModel ();

        /**
         * Ustawia całą listę dzieci. Ta metoda nie może być szablonem, bo
         * musi być wirtualna. Modyfikuje podaną listę (ustawia dzieciom parenty
         * na siebie).
         */
        void setChildren (Base::WidgetCollection *e);

        /**
         * Dodaje listę dzieci do już istniejących .
         */
        void addChildren (Base::WidgetCollection *e);

        /**
         * Dodaje dziecko.
         */
        virtual void addChild (Base::WidgetChildType e)
        {
                children.push_back (e);
                e->setParent (this);
        }

        /**
         * Usuwa dziecko.
         */
        void removeChild (Base::WidgetChildType e);

        /**
         * Usuwa wszystie dzieci.
         */
        void clearChildren ();

        /// Czy ma dzieci.
        bool hasChildren () const;

private:

/*------owner / controller / widget-----------------------------------------*/

        Base::WidgetOwnerType getOwner () { return owner; }
        Base::WidgetOwnerConstType getOwner () const { return owner; }
        void setOwner (Base::WidgetOwnerType o) { owner = o; }

private:

        Base::WidgetCollection children;
        Base::WidgetParentType parent;
        Ptr <Model::IModel> model;
        Base::WidgetOwnerType owner;

};

}// namespace

#	endif /* TREEWIDGET_H_ */
