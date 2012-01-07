/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMODELAWARE_H_
#define IMODELAWARE_H_

#include <vector>

#include "TreeSlaveIterator.h"
#include "Types.h"
#include "Pointer.h"

namespace Model {

/**
 * Typ właściciela modelu. Dziedziczą z tego kontrolery i widgety, do których potem
 * TreeModel i ModelIterator mają referencję i mogą pobrać z nich model. Ten typ
 * jest potrzebny po to, żeby model mógł mieć ownera zarówno kontroler jak i widget.
 * \ingroup Tree
 */
struct IModelAware {

        virtual ~IModelAware () {}

        /*
         * Słowo wyjaśnienia na temat typu zwracanego z tego gettera. Ptr <IModel> to
         * typ pola w kontrolerach i widgetach (Ptr <IModel> model). Zwracam referecję
         * do tego, żeby uniknąć kopiowania. Kopiowanie tworzy zmienne tymczasowe i powoduje
         * warningi w iteratorach (taking address of temporary), które wyłuskują model z
         * kontrolerów i widgetów w locie.
         *
         * Metoda nie jest const, ponieważ wskaźnik nie jest do stałej i można zmodyfikować
         * model pobrany przez getModel.
         */
        virtual Ptr <IModel> const &getModel () = 0;
        virtual void setModel (Ptr <IModel> m) = 0;

        /// Dziwne nazwy pozwalają uniknąć konfliktu nazw.
        virtual IModelAware *getParentMAW () = 0;
        /// Dziwne nazwy pozwalają uniknąć konfliktu nazw.
        virtual bool hasChildrenMAW () const = 0;
        // TODO niespójna nazwa
        virtual bool ownsChildren () const = 0;

        // Typy tych iteratorów są dostosowane do iteratorów z kolekcji STL.
        virtual ModelConstIter beginForModel () const = 0;
        virtual ModelIter beginForModel () = 0;
        virtual ModelConstIter endForModel () const = 0;
        virtual ModelIter endForModel () = 0;

};

} // nam

#	endif /* IMODELAWARE_H_ */
