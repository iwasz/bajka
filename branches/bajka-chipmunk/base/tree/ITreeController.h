/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITREEMASTER_H_
#define ITREEMASTER_H_

#include "Types.h"
#include "IModelAware.h"

namespace Controller {

/**
 * Interfejs udostępniający metody struktury drzewiastej dla kontrolerów. Z tego interfejsu 
 * dziedziczy kazdy kontroler. Kontrolery mogą tworzyć strukturę drzewiastą i udostępniać ja
 * modelom i widgetom, tak, że modele i widgety mają dostęp do swoich "potomków" i "rodziców",
 * ale nie bezpośrednio, tylko właśnie poprzez kontroler.
 * \ingroup Tree
 */
struct  ITreeController : public Model::IModelAware {

        typedef ControllerIter iterator;
        typedef ControllerConstIter const_iterator;

        virtual ~ITreeController () {}

/*------parents-------------------------------------------------------------*/

        /// Zwraca rodzica.
        virtual ControllerParentType getParent () = 0;
        /// Zwraca rodzica.
        virtual ControllerParentConstType getParent () const = 0;
        /// Ustawia rodzica.
        virtual void setParent (ControllerParentType p) = 0;

/*------children------------------------------------------------------------*/

        /// Iterator do kolekcji dzieci.
        virtual ControllerConstIter begin () const = 0;
        /// Iterator do kolekcji dzieci.
        virtual ControllerIter begin () = 0;
        /// Iterator do kolekcji dzieci.
        virtual ControllerConstIter end () const = 0;
        /// Iterator do kolekcji dzieci.
        virtual ControllerIter end () = 0;

        /// Iterator do kolekcji dzieci, ale z kazdego dziecka zwracany jest tylko obiekt IWidget.
        virtual View::WidgetConstIter beginForWidget () const = 0;
        /// Iterator do kolekcji dzieci, ale z kazdego dziecka zwracany jest tylko obiekt IWidget.
        virtual View::WidgetIter beginForWidget () = 0;
        /// Iterator do kolekcji dzieci, ale z kazdego dziecka zwracany jest tylko obiekt IWidget.
        virtual View::WidgetConstIter endForWidget () const = 0;
        /// Iterator do kolekcji dzieci, ale z kazdego dziecka zwracany jest tylko obiekt IWidget.
        virtual View::WidgetIter endForWidget () = 0;

        /**
         * Ustawia całą listę dzieci (usuwając te które już były). 
         */
        virtual void setChildren (ControllerCollection *e) = 0;

        /**
         * Dodaje listę dzieci do już istniejących.
         */
        virtual void addChildren (ControllerCollection *e) = 0;

        /**
         * Dodaje dziecko.
         */
        virtual void addChild (ControllerChildType e) = 0;

        /**
         * Usuwa dziecko.
         */
        virtual void removeChild (ControllerChildType e) = 0;

        /**
         * Usuwa wszystie dzieci.
         */
        virtual void clearChildren () = 0;

        /**
         * Zwraca informację, czy są jakieś dzieci, czy nie. W założeniu ma być szybsza niż porównanie
         * begin z end.
         */
        virtual bool hasChildren () const = 0;
};

} // namespace

#	endif /* ITREEMASTER_H_ */
