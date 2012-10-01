/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEL_LAYOUT_H_
#define BAJKA_MODEL_LAYOUT_H_

#include "geometry/Point.h"
#include "util/ReflectionMacros.h"
#include "IGroupProperties.h"
#include "Align.h"

namespace Model {
struct IModel;

/**
 * Wałaściwości obiektu, który jest wewnątrz Model::RelativeGroup. Te właściwości definiują
 * rozmiary i położenie obiektu, który jest wewnątrz Model::RelativeGroup. Kiedy są ustawione,
 * to przesunięcie i rozmiary obiektu (Model::IModel::setTranslate etc) nie są brane pod
 * uwagę.
 */
struct RelativeGroupProperties : public IGroupProperties {

        C__ (void)
        RelativeGroupProperties () :
                hAlign (HA_CENTER),
                vAlign (VA_CENTER),
                width (-1),
                height (-1),
                translate (Geometry::makePoint (0, 0)) {}

        virtual ~RelativeGroupProperties () {}

        /**
         * Wyrównanie w poziomie.
         */
        HAlign pe_ (hAlign);

        /**
         * Wyrównanie w pionie.
         */
        VAlign pe_ (vAlign);

        /**
         * Szerokość w procentach. To pole jest brane pod uwagę tylko w przypadku, gdy model, któremu je usawimy
         * implementuje Model::IBox i nie są nałożone na niego trasformacje obrotu i skali. Czyli jednym słowem
         * pudełko równoległe do osi i bez skalowania. Wartość ujemna nie jest brana pod uwagę.
         */
        float p_ (width);

        /**
         * Wysokość w procentach. To pole jest brane pod uwagę tylko w przypadku, gdy model, któremu je usawimy
         * implementuje Model::IBox i nie są nałożone na niego trasformacje obrotu i skali. Czyli jednym słowem
         * pudełko równoległe do osi i bez skalowania. Wartość ujemna nie jest brana pod uwagę.
         */
        float p_ (height);

        /**
         * Przesunięcie względem rozmiarów rodzica. Działa tylko w gdy rodzic jest
         * typu RelativeGroup. Jednostką jest procent. <del>Wartość ujemna któregoś z koordynatów
         * oznacza wartość nieustaloną i nie brana pod uwagę.</del>
         */
        Geometry::Point P_ (translate);

        E_ (RelativeGroupProperties)
};

} /* namespace Model */

#	endif /* LAYOUT_H_ */
