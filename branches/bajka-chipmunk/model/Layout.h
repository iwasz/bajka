/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEL_LAYOUT_H_
#define BAJKA_MODEL_LAYOUT_H_

#include "../geometry/Point.h"
#include "../util/ReflectionMacros.h"

namespace Model {
struct IModel;

struct Layout {

        C__ (void)
        Layout () : align ((Align)(HCENTER | TOP)), translateRel (-1, -1) {}

        /**
         * Przesunięcie względem rozmiarów rodzica. Działa tylko w gdy rodzic jest
         * typu BoxGroup. Ujemne oznacza nieustawione.
         */
        m_ (setTranslateRel) void setTranslateRel (Geometry::Point const &t) { translateRel = t; }
        void resetTranslateRel () { translateRel.x = -1; }
        Geometry::Point const &getTranslateRel () const { return translateRel; }

        enum Align {
                TOP     = 0x01,
                BOTTOM  = 0x02,
                VCENTER = 0x04,
                LEFT    = 0x08,
                RIGHT   = 0x10,
                HCENTER = 0x20
        };

        Align getAlign () const { return align; }
        m_ (setAlign) void setAlign (Align a) { align = a; }

/*--------------------------------------------------------------------------*/

        /**
         * @param m Model którego dotyczy request
         * @param origTranslate Aktualne przesunięcie tego modelu.
         * @param w Aktualna wysokość boundingBoxa modelu m
         * @param h Aktualna szerokość boundingBoxa modelu m
         */
        Geometry::Point calculateTranslation (IModel const *m, Geometry::Point const &currentTranslate, double aabbW, double aabbH) const;

private:

        Align align;
        Geometry::Point translateRel;

        E_ (Layout)
};

} /* namespace Model */

#	endif /* LAYOUT_H_ */
