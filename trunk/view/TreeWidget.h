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
#include "IModel_t.h"
#include "../base/tree/Types.h"

namespace View {

/**
 * Implementuje strukturę drzewiastą widgetów. Prócz zagnieżdżania kontrolerów można
 * także zagnieżdżać widgety. Jednak zagnieżdżanie widgetów skutkuje jedynie ich wizualnym
 * grupowaniem. Wszystkie zagnieżdżone widgety mają ten sam ukłąd współrzędnych.
 * \ingroup Tree
 */
class TreeWidget : public IWidget {
public:

        typedef WidgetIter iterator;
        typedef WidgetConstIter const_iterator;

        TreeWidget () : model (), children (), parent (), owner () {}
        virtual ~TreeWidget () {}

/*------IModelAware---------------------------------------------------------*/

        virtual Ptr <Model::IModel> const &getModel () { return model; }
        virtual void setModel (Ptr <Model::IModel> m);

        Model::IModelAware *getParentMAW () { return parent; }
        bool hasChildrenMAW () const { return hasChildren (); }

/*------parents-------------------------------------------------------------*/

        WidgetParentType getParent ();
        WidgetParentConstType getParent () const;
        void setParent (WidgetParentType p) { parent = p; }

/*------children------------------------------------------------------------*/

        WidgetConstIter begin () const;
        WidgetIter begin ();
        WidgetConstIter end () const;
        WidgetIter end ();

        Model::ModelConstIter beginForModel () const;
        Model::ModelIter beginForModel ();
        Model::ModelConstIter endForModel () const;
        Model::ModelIter endForModel ();

        /**
         * Ustawia całą listę dzieci. Ta metoda nie może być szablonem, bo
         * musi być wirtualna. Modyfikuje podaną listę (ustawia dzieciom parenty
         * na siebie).
         */
        void setChildren (WidgetCollection *e);

        /**
         * Dodaje listę dzieci do już istniejących .
         */
        void addChildren (WidgetCollection *e);

        /**
         * Dodaje dziecko.
         */
        virtual void addChild (WidgetChildType e)
        {
                children.push_back (e);
                e->setParent (this);
        }

        /**
         * Usuwa dziecko.
         */
        void removeChild (WidgetChildType e);

        /**
         * Usuwa wszystie dzieci.
         */
        void clearChildren ();

        /// Czy ma dzieci.
        bool hasChildren () const;

private:

/*------owner / controller / widget-----------------------------------------*/

        WidgetOwnerType getOwner () { return owner; }
        WidgetOwnerConstType getOwner () const { return owner; }
        void setOwner (WidgetOwnerType o) { owner = o; }

protected:

        Ptr <Model::IModel> model;

private:

        WidgetCollection children;
        WidgetParentType parent;
        WidgetOwnerType owner;

};

}// namespace

#	endif /* TREEWIDGET_H_ */
