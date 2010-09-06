/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IWIDGET_H_
#define IWIDGET_H_

#include <Reflection.h>
#include <collection/Map.h>
#include <collection/List.h>

#include <List.h>
#include <Vector.h>

#include "IView.h"
#include "../util/tree/ITreeMasterSlave.h"

namespace Model {
class IModel;
}

namespace View {

/**
 * Szczególny rodzaj widoku współpracujący z kontrolerami i modelami. Część
 * triady MVC. Iterfejs IView jest jeszcze bardziej ogólny.
 * \ingroup View
 */
struct IWidget :
        public IView,
        public virtual Util::ITreeMasterSlave <IWidget> {

        virtual ~IWidget () {}

        /**
         * Inits this Widget. You must reimplemet this method if you want
         * your View to be statefull, and perform dynamic_pointer_cast to
         * your preffered model concrete type. Also ypu should call init
         * from parent class.
         */
        virtual void setModel (Ptr <Model::IModel> model) = 0;
        // Świadomie nie mam const na końcu, bo swracam wskaźnik do niestałego modelu.
        virtual Ptr <Model::IModel> getModel () = 0;

        /**
         * Zwraca informację czy widget jest wodoczny, czy nie.
         * @return
         */
        virtual bool getVisible () const = 0;

        /**
         * Ustawiainformację czy widget jest wodoczny, czy nie.
         * @return
         */
        virtual void setVisible (bool) = 0;
};

/****************************************************************************/

typedef Reflection::List <Ptr <IWidget> > WidgetList;

typedef Core::Vector <Ptr <IWidget> > WidgetVector;
/// \todo Klucz dałbym na std::string
typedef Reflection::Map <Core::String, Ptr <IWidget> > StringWidgetMap;
_f (StringWidgetMap)

}

#	endif /* IWIDGET_H_ */
