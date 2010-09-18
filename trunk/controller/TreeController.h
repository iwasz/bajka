/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TREECONTROLLER_H_
#define TREECONTROLLER_H_

#include <Reflection.h>
#include <List.h>
#include <collection/List.h>

#include "IController.h"
#include "IWidget.h"
#include "IModel_t.h"

namespace Controller {

/**
 * Implementuje strukturę drzewiastą kontrolerów. Kazdy kontroler można zagniexdzić w 
 * innym, tak, żeby tworzył drzewo. Do tej struktury drzewiastej mają dostęp także modele
 * i widgety podpięte do kontrolerów, ale w ten sposób, że widgety mają dostęp do child-
 * widgetów, a modele tyko do modeli.
 * \inplace Util
 */
class TreeController : public IController {
public:
        __d

        TreeController () : children (), parent (), model () {}
        virtual ~TreeController () {}

/*------IModelAware---------------------------------------------------------*/

        _m (getModel) Ptr <Model::IModel> const &getModel () { return model; }
        _m (setModel) void setModel (Ptr <Model::IModel> m);

        Model::IModelAware *getParentMAW () { return parent; }
        bool hasChildrenMAW () const { return hasChildren (); }

/*--------------------------------------------------------------------------*/

        IController *getParent () { return parent; }
        IController const *getParent () const { return parent; }
        void setParent (IController *p) { parent = p; }

/*------Iteratory-----------------------------------------------------------*/

        ControllerConstIter begin () const;
        ControllerIter begin ();
        ControllerConstIter end () const;
        ControllerIter end ();

        Model::ModelConstIter beginForModel () const;
        Model::ModelIter beginForModel ();
        Model::ModelConstIter endForModel () const;
        Model::ModelIter endForModel ();

        View::WidgetConstIter beginForWidget () const;
        View::WidgetIter beginForWidget ();
        View::WidgetConstIter endForWidget () const;
        View::WidgetIter endForWidget ();

/*--------------------------------------------------------------------------*/

        /**
         * Ustawia całą listę dzieci. Używa addChild.
         */
        void setChildren (ControllerCollection *e);

        /**
         * Dodaje listę dzieci do już istniejących. Używa addChild.
         */
        void addChildren (ControllerCollection *e);

        /**
         * Dodaje dziecko.
         */
        virtual void addChild (ControllerChildType e)
        {
                children.push_back (e);
                e->setParent (dynamic_cast <ControllerParentType> (this));
        }

        /**
         * Usuwa pierwsze dziecko o wartości równej e. Ustawia mu także parent na NULL.
         */
        void removeChild (ControllerChildType e);

        /**
         * Czyści listę dzieci. Ustawia wszystkim parent na NULL.
         */
        void clearChildren ();

        bool hasChildren () const { return !children.empty (); }

private:

        ControllerCollection children;
        ControllerParentType parent;

protected:

        Ptr <Model::IModel> model;

        _m (init)
        _m (getWidget)
        _m (setWidget)
        _m (getMapping)
        _e (TreeController)
};

}

#	endif /* TREECONTROLLER_H_ */
