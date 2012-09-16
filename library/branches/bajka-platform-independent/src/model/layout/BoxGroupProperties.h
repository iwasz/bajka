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
#include "Padding.h"

namespace Model {
struct IModel;

/**
 * Wałaściwości obiektu, który jest wewnątrz Model::BoxGroup. Te właściwości definiują
 * rozmiary i położenie obiektu, który jest wewnątrz Model::BoxGroup. Kiedy są ustawione,
 * to przesunięcie i rozmiary obiektu (Model::IModel::setTranslate etc) nie są brane pod
 * uwagę.
 */
struct BoxGroupProperties : public IGroupProperties {

        C__ (void)
        BoxGroupProperties () :
                align ((HCENTER | TOP)),
                width (-1),
                height (-1),
                translate (Geometry::makePoint (-1, -1))/*,
                padding (NULL),
                wrapContentsW (false),
                wrapContentsH (false)*/ {}

        virtual ~BoxGroupProperties () {}

        enum Align {
                TOP     = 0x01,
                BOTTOM  = 0x02,
                VCENTER = 0x04,
                LEFT    = 0x08,
                RIGHT   = 0x10,
                HCENTER = 0x20
        };

        /**
         * Przesunięcie względem rozmiarów rodzica. Działa tylko w gdy rodzic jest
         * typu BoxGroup. Jednostką jest procent. Wartość ujemna któregoś z koordynatów
         * oznacza wartość nieustaloną i nie brana pod uwagę.
         */
        void setTranslate (Geometry::Point const &t) { translate = t; }

        /**
         * Przesunięcie względem rozmiarów rodzica. Działa tylko w gdy rodzic jest
         * typu BoxGroup. Jednostką jest procent. Wartość ujemna któregoś z koordynatów
         * oznacza wartość nieustaloną i nie brana pod uwagę.
         */
        Geometry::Point const &getTranslate () const { return translate; }

        /**
         * Justowanie. Justowanie działa tylko gdy ustawiono translate.
         */
        int getAlign () const { return align; }

        /**
         * Justowanie. Justowanie działa tylko gdy ustawiono translate.
         */
        void setAlign (int a) { align = a; }

//        Padding const *getPadding () const { return padding; }
//        void setPadding (Padding *p) { padding = p; }
//
//        bool getWrapContentsW () const { return wrapContentsW; }
//        void setWrapContentsW (bool b) { wrapContentsW = b; }
//
//        bool getWrapContentsH () const { return wrapContentsH; }
//        void setWrapContentsH (bool b) { wrapContentsH = b; }

        /**
         * Szerokość w procentach. To pole jest brane pod uwagę tylko w przypadku, gdy model, któremu je usawimy
         * implementuje Model::IBox i nie są nałożone na niego trasformacje obrotu i skali. Czyli jednym słowem
         * pudełko równoległe do osi i bez skalowania. Wartość ujemna nie jest brana pod uwagę.
         */
        float getWidth () const { return width; }

        /**
         * Szerokość w procentach. To pole jest brane pod uwagę tylko w przypadku, gdy model, któremu je usawimy
         * implementuje Model::IBox i nie są nałożone na niego trasformacje obrotu i skali. Czyli jednym słowem
         * pudełko równoległe do osi i bez skalowania. Wartość ujemna nie jest brana pod uwagę.
         */
        void setWidth (float f) { width = f; }

        /**
         * Wysokość w procentach. To pole jest brane pod uwagę tylko w przypadku, gdy model, któremu je usawimy
         * implementuje Model::IBox i nie są nałożone na niego trasformacje obrotu i skali. Czyli jednym słowem
         * pudełko równoległe do osi i bez skalowania.  Wartość ujemna nie jest brana pod uwagę.
         */
        float getHeight () const { return height; }

        /**
         * Wysokość w procentach. To pole jest brane pod uwagę tylko w przypadku, gdy model, któremu je usawimy
         * implementuje Model::IBox i nie są nałożone na niego trasformacje obrotu i skali. Czyli jednym słowem
         * pudełko równoległe do osi i bez skalowania. Wartość ujemna nie jest brana pod uwagę.
         */
        void setHeight (float f) { height = f; }

private:

        int             p_ (align);
        float           p_ (width);
        float           p_ (height);
        Geometry::Point P_ (translate);
//        Padding *       p_ (padding);
//        bool            p_ (wrapContentsW);
//        bool            p_ (wrapContentsH);

        E_ (BoxGroupProperties)
};

} /* namespace Model */

#	endif /* LAYOUT_H_ */
