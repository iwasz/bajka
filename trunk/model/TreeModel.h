/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TREEMODEL_H_
#define TREEMODEL_H_

#include "IModel.h"
#include "../base/tree/IModelAware.h"
#include "../base/tree/Types.h"

namespace Model {

/**
 * Implementuje dostęp do struktury drzewiastej dla modelu. Struktura ta jest utrzymywana w
 * obiekcie ownera, który może być kontrolerem, lub widgetem. 
 * \ingroup Tree
 */
class TreeModel : public IModel {
public:

        TreeModel (): owner (0) {}
        virtual ~TreeModel () {}

/*------parents-------------------------------------------------------------*/

        /// Zwraca rodzica tego modelu.
        ModelParentType getParent ();
        /// Zwraca rodzica tego modelu.
        ModelParentConstType getParent () const;

/*------children------------------------------------------------------------*/

        /// Iterator do początku kolekcji potomków tego modelu (przez owner).
        ModelConstIter begin () const;
        /// Iterator do początku kolekcji potomków tego modelu (przez owner).
        ModelIter begin ();
        /// Iterator do końca kolekcji potomków tego modelu (przez owner).
        ModelConstIter end () const;
        /// Iterator do końca kolekcji potomków tego modelu (przez owner).
        ModelIter end ();

        /// Zwraca informację czy są jacyś potomkowie tego modelu.
        bool hasChildren () const;

private:

/*------owner / controller / widget-----------------------------------------*/

        /// Zwraca obiekt ownera, czyli kontroler, lub widget, który zawiera ten model.
        ModelOwnerType getOwner () { return owner; }
        /// Zwraca obiekt ownera, czyli kontroler, lub widget, który zawiera ten model.
        ModelOwnerConstType getOwner () const { return owner; }
        /// Ustawia obiekt ownera, czyli kontroler, lub widget, który zawiera ten model.
        void setOwner (ModelOwnerType o) { owner = o; }

private:

        ModelOwnerType owner;

};

} // nam

#	endif /* TREEMODEL_H_ */
