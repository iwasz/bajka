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
#include "IModel.h"
#include "IWidget.h"

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

        Base::IModelAware *getParentMAW () { return parent; }
        bool hasChildrenMAW () const { return hasChildren (); }

/*--------------------------------------------------------------------------*/

        IController *getParent () { return parent; }
        IController const *getParent () const { return parent; }
        void setParent (IController *p) { parent = p; }

/*------Iteratory-----------------------------------------------------------*/

        Base::ControllerConstIter begin () const;
        Base::ControllerIter begin ();
        Base::ControllerConstIter end () const;
        Base::ControllerIter end ();

        Base::ModelConstIter beginForModel () const;
        Base::ModelIter beginForModel ();
        Base::ModelConstIter endForModel () const;
        Base::ModelIter endForModel ();

        Base::WidgetConstIter beginForWidget () const;
        Base::WidgetIter beginForWidget ();
        Base::WidgetConstIter endForWidget () const;
        Base::WidgetIter endForWidget ();

/*--------------------------------------------------------------------------*/

        /**
         * Ustawia całą listę dzieci. Używa addChild.
         */
        void setChildren (Base::ControllerCollection *e);

        /**
         * Dodaje listę dzieci do już istniejących. Używa addChild.
         */
        void addChildren (Base::ControllerCollection *e);

        /**
         * Dodaje dziecko.
         */
        virtual void addChild (Base::ControllerChildType e)
        {
                children.push_back (e);
                e->setParent (dynamic_cast <Base::ControllerParentType> (this));
        }

        /**
         * Usuwa pierwsze dziecko o wartości równej e. Ustawia mu także parent na NULL.
         */
        void removeChild (Base::ControllerChildType e);

        /**
         * Czyści listę dzieci. Ustawia wszystkim parent na NULL.
         */
        void clearChildren ();

        bool hasChildren () const { return !children.empty (); }

private:

        Base::ControllerCollection children;
        Base::ControllerParentType parent;

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
