/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GROUP_PROPERTIES_MODEL_LAYOUT_H_
#define GROUP_PROPERTIES_MODEL_LAYOUT_H_

#include "util/ReflectionMacros.h"
#include "IGroupProperties.h"

namespace Model {
struct IModel;

/**
 * Wałaściwości obiektu, który jest zawarty bezpośrednio w Grupie.
 */
struct LayerProperties : public IGroupProperties {

        C__ (void)
        LayerProperties () : fillW (true), fillH (true), centerGroup (true) {}

        virtual ~LayerProperties () {}

        /**
         * Rozciągnij się do rozmiarów grupy w której jesteś.
         */
        bool p_ (fillW)

        /**
         * Rozciągnij się do rozmiarów grupy w której jesteś.
         */
        bool p_ (fillH)

        /**
         * Wycentruj na środku rodzica (działa tylko dla grup).
         */
        bool p_ (centerGroup)

        E_ (LayerProperties)
};

} /* namespace Model */

#	endif /* LAYOUT_H_ */
