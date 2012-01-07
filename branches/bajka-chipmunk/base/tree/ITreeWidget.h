/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITREEMASTERSLAVE_H_
#define ITREEMASTERSLAVE_H_

#include "Types.h"
#include "IModelAware.h"
#include "ITreeController.h"

namespace View {

/**
 * Typ właściciela widgetu. Jest to oczywiście kontroler. Typ nie jest zdefiniowany w 
 * Types.h, bo nie można tam includować ITreeController.h.
 * \ingroup Tree
 */
typedef Controller::ITreeController WidgetOwnerBaseType;

/**
 * Typ wskaźnika do właściciela widgetu. Jest to oczywiście kontroler. Typ nie jest zdefiniowany w 
 * Types.h, bo nie można tam includować ITreeController.h.
 * \ingroup Tree
 */
typedef View::WidgetOwnerBaseType *WidgetOwnerType;

/**
 * Typ wskaźnika do właściciela widgetu. Jest to oczywiście kontroler. Typ nie jest zdefiniowany w 
 * Types.h, bo nie można tam includować ITreeController.h.
 * \ingroup Tree
 */
typedef View::WidgetOwnerBaseType const *WidgetOwnerConstType;

/**
 * Interfejs udostępniający metody pobierające dzieci i rodziców tego widgeta. Widgety mogą same
 * tworzyć struktury drzewiaste lub mogą być podpięte pod kontroler i czerpac informację o swoich
 * potomkach i rodzicach z kontrolera. Czyli struktura drzewiasta widgetu może być stworzona na 2
 * sposoby!
 * \ingroup Tree
 */
struct ITreeWidget : public Model::IModelAware {

        /// Typ iteratora dla dzieci widgeta.
        typedef WidgetIter iterator;
        /// Typ iteratora dla dzieci widgeta.
        typedef WidgetConstIter const_iterator;

        virtual ~ITreeWidget () {}

/*------parents-------------------------------------------------------------*/

        virtual WidgetParentType getParent () = 0;
        virtual WidgetParentConstType getParent () const = 0;
        virtual void setParent (WidgetParentType p) = 0;

/*------owner / controller / widget-----------------------------------------*/

        /// Zwraca rodzica tego widgetu.
        virtual WidgetOwnerType getOwner () = 0;
        /// Zwraca rodzica tego widgetu.
        virtual WidgetOwnerConstType getOwner () const = 0;
        /// Ustawia rodzica tego widgetu.
        virtual void setOwner (WidgetOwnerType) = 0;

/*------children------------------------------------------------------------*/

        // Iterator do początku kolekcji dzieci.
        virtual WidgetConstIter begin () const = 0;
        virtual WidgetIter begin () = 0;
        virtual WidgetConstIter end () const = 0;
        virtual WidgetIter end () = 0;

        /**
         * Ustawia całą listę dzieci. Ta metoda nie może być szablonem, bo
         * musi być wirtualna. Modyfikuje podaną listę (ustawia dzieciom parenty
         * na siebie).
         */
        virtual void setChildren (WidgetCollection *e) = 0;

        /**
         * Dodaje listę dzieci do już istniejących .
         */
        virtual void addChildren (WidgetCollection *e) = 0;

        /**
         * Dodaje dziecko.
         */
        virtual void addChild (WidgetChildType e) = 0;

        /**
         * Usuwa dziecko.
         */
        virtual void removeChild (WidgetChildType e) = 0;

        /**
         * Usuwa wszystie dzieci.
         */
        virtual void clearChildren () = 0;

        /// Czy są dzieci
        virtual bool hasChildren () const = 0;

        /// true jeśli ma dzieci dodane bezpośrednio do widgeta, a nie do kontrolera.
        virtual bool ownsChildren () const = 0;
};

} // namespace

#	endif /* ITREEMASTERSLAVE_H_ */
