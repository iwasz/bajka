/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCREEN_GROUP_PROPERTIES_MODEL_LAYOUT_H_
#define SCREEN_GROUP_PROPERTIES_MODEL_LAYOUT_H_

#include "geometry/Point.h"
#include "util/ReflectionMacros.h"
#include "IGroupProperties.h"
#include "Align.h"

namespace Model {
struct IModel;

/**
 * Wałaściwości obiektu, który jest zawarty bezpośrednio w ekranie, czyli jest ROOTem scene-grafu.
 */
struct ScreenGroupProperties : public IGroupProperties {

        C__ (void)
        ScreenGroupProperties () : fillW (true), fillH (true) {}

        virtual ~ScreenGroupProperties () {}

        /**
         * Wypełnij widoczną cześć ekranu w całej szerokości.
         */
        bool p_ (fillW)

        /**
         * Wypełnij widoczną cześć ekranu w całej wysokości.
         */
        bool p_ (fillH)


        E_ (ScreenGroupProperties)
};

} /* namespace Model */

#	endif /* LAYOUT_H_ */
