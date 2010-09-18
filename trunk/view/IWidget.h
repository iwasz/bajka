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
#include <List.h>
#include <Vector.h>

#include "IView.h"
#include "../base/tree/ITreeWidget.h"

namespace View {

/**
 * Szczególny rodzaj widoku współpracujący z kontrolerami i modelami. Część
 * triady MVC. Iterfejs IView jest jeszcze bardziej ogólny.
 * \ingroup View
 */
struct IWidget :
        public IView,
        public ITreeWidget {

        virtual ~IWidget () {}

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

/// \todo Klucz dałbym na std::string
typedef Reflection::Map <Core::String, Ptr <IWidget> > StringWidgetMap;
_f (StringWidgetMap)

}

#	endif /* IWIDGET_H_ */
