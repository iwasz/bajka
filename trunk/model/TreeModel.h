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
//#include "IWidget.h" // TODO do wywalenia jak mi sie uda zlokalizować skąd leci forward
#include "../base/tree/IModelAware.h"
#include "../base/tree/Types.h"

namespace Model {

/**
 * Implementuje dostęp do struktury drzewiastej dla modelu. Struktura ta jest utrzymywana w
 * obiekcie ownera, który może być kontrolerem, lub widgetem. 
 * \inplace Util
 */
class TreeModel : public IModel {
public:

        TreeModel (): owner () {}
        virtual ~TreeModel () {}

/*------parents-------------------------------------------------------------*/

        /// Zwraca rodzica tego modelu.
        Base::ModelParentType getParent ();
        /// Zwraca rodzica tego modelu.
        Base::ModelParentConstType getParent () const;

/*------children------------------------------------------------------------*/

        /// Iterator do początku kolekcji potomków tego modelu (przez owner).
        Base::ModelConstIter begin () const;
        /// Iterator do początku kolekcji potomków tego modelu (przez owner).
        Base::ModelIter begin ();
        /// Iterator do końca kolekcji potomków tego modelu (przez owner).
        Base::ModelConstIter end () const;
        /// Iterator do końca kolekcji potomków tego modelu (przez owner).
        Base::ModelIter end ();

        /// Zwraca informację czy są jacyś potomkowie tego modelu.
        bool hasChildren () const;

private:

/*------owner / controller / widget-----------------------------------------*/

        /// Zwraca obiekt ownera, czyli kontroler, lub widget, który zawiera ten model.
        Base::ModelOwnerType getOwner () { return owner; }
        /// Zwraca obiekt ownera, czyli kontroler, lub widget, który zawiera ten model.
        Base::ModelOwnerConstType getOwner () const { return owner; }
        /// Ustawia obiekt ownera, czyli kontroler, lub widget, który zawiera ten model.
        void setOwner (Base::ModelOwnerType o) { owner = o; }

private:

        Base::ModelOwnerType owner;

};

} // nam

#	endif /* TREEMODEL_H_ */
