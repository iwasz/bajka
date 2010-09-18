/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TYPES_H_
#define TYPES_H_

#include <Reflection.h>
#include <list>
#include <collection/List.h>

#include "TreeSlaveIterator.h"
#include "Extractors.h"

namespace Model {
class IModel;
}

namespace View {
class IWidget;
}

namespace Controller {
class IController;
}

namespace Base {
class IModelAware;

/**
 * Wspólny plik nagłówkowy, ponieważ w wielu miejscach potrzebne jest wiele
 * typów, na przykłąd kontroler potrzebuje typów widgeta i modelu etc.
 */
template <typename Element>
struct TreeTraits {

        /// Typ bez żadnych modyfikacji, czyli nie wskaźnik, nie ref, tylko samiuteńki typ.
        typedef Element ChildBaseType;
        /// Typ bez żadnych modyfikacji, czyli nie wskaźnik, nie ref, tylko samiuteńki typ.
        typedef Element ParentBaseType;

        /// Typ dzieci. Jest to wskaźnik Ptr do elementu Element.
        typedef Ptr <Element> ChildType;
        // Const nusi być po Ptr (a nie po Element), bo kontenery STL też tak definiują robią.
        typedef Ptr <Element> const ChildConstType;

        /// Typ rodzica- zwykły wskaźnik do Element.
        typedef Element *ParentType;
        typedef Element const *ParentConstType;

// TODO Po niezbędnych zmianach w Tiliae przywrócić starą wersję z std::list.
        typedef typename Reflection::List <ChildType> ChildCollection;
//        typedef typename std::list <ChildType> ChildCollection;

        // Główne iteratory.
        typedef typename ChildCollection::iterator ChildIter;
        typedef typename ChildCollection::const_iterator ChildConstIter;
};

/*# kontroler ##############################################################*/

typedef TreeTraits <Controller::IController>::ChildBaseType ControllerChildBaseType;
typedef TreeTraits <Controller::IController>::ParentBaseType ControllerParentBaseType;

typedef TreeTraits <Controller::IController>::ChildType ControllerChildType;
typedef TreeTraits <Controller::IController>::ChildConstType ControllerChildConstType;

typedef TreeTraits <Controller::IController>::ParentType ControllerParentType;
typedef TreeTraits <Controller::IController>::ParentConstType ControllerParentConstType;

typedef TreeTraits <Controller::IController>::ChildCollection ControllerCollection;
_f (ControllerCollection)

typedef TreeTraits <Controller::IController>::ChildIter ControllerIter;
typedef TreeTraits <Controller::IController>::ChildConstIter ControllerConstIter;

/*# widget #################################################################*/

typedef TreeTraits <View::IWidget>::ChildBaseType WidgetChildBaseType;
typedef TreeTraits <View::IWidget>::ParentBaseType WidgetParentBaseType;

typedef TreeTraits <View::IWidget>::ChildType WidgetChildType;
typedef TreeTraits <View::IWidget>::ChildConstType WidgetChildConstType;

typedef TreeTraits <View::IWidget>::ParentType WidgetParentType;
typedef TreeTraits <View::IWidget>::ParentConstType WidgetParentConstType;

typedef TreeTraits <View::IWidget>::ChildCollection WidgetCollection;
_f (WidgetCollection)

typedef TreeIter <Ptr <View::IWidget>,
                ControllerCollection::iterator,
                WidgetPtrExtractor,
                WidgetCollection::iterator,
                NoopExtractor> WidgetIter;

typedef TreeIter <Ptr <View::IWidget> const,
                ControllerCollection::const_iterator,
                WidgetPtrExtractor,
                WidgetCollection::const_iterator,
                NoopExtractor> WidgetConstIter;

/*# model ##################################################################*/

typedef TreeTraits <Model::IModel>::ChildBaseType ModelChildBaseType;
typedef TreeTraits <Model::IModel>::ParentBaseType ModelParentBaseType;

typedef TreeTraits <Model::IModel>::ChildType ModelChildType;
typedef TreeTraits <Model::IModel>::ChildConstType ModelChildConstType;

typedef TreeTraits <Model::IModel>::ParentType ModelParentType;
typedef TreeTraits <Model::IModel>::ParentConstType ModelParentConstType;

/**
 * Iterator zwracany z TreeModel::begin i TreeModel::end. Zaimplementowane zarówno
 * w TreeController::beginForModel jak i TreeWidget (te implementacje dostarczają
 * iteratorów modelowi).
 */
typedef TreeIter <Ptr <Model::IModel>,
                ControllerCollection::iterator,
                ModelPtrExtractor,
                WidgetCollection::iterator,
                ModelPtrExtractor> ModelIter;

/**
 * Iterator zwracany z TreeModel::begin i TreeModel::end. Zaimplementowane zarówno
 * w TreeController::beginForModel jak i TreeWidget (te implementacje dostarczają
 * iteratorów modelowi).
 */
typedef TreeIter <Ptr <Model::IModel> const,
                ControllerCollection::const_iterator,
                ModelPtrExtractor,
                WidgetCollection::const_iterator,
                ModelPtrExtractor> ModelConstIter;

typedef IModelAware ModelOwnerBaseType;
typedef ModelOwnerBaseType *ModelOwnerType;
typedef ModelOwnerBaseType const *ModelOwnerConstType;

}// nam

#	endif /* TYPES_H_ */
