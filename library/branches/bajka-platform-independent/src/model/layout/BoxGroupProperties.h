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
                translate (Geometry::makePoint (0, 0)),
                padding (NULL),
                expand (false),
                shrink (false) {}

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
         * typu BoxGroup. Ujemne oznacza nieustawione. Jednostką jest procent.
         */
        void setTranslate (Geometry::Point const &t) { translate = t; }


//        void resetTranslate () { translateRel.x = -1; }

        /**
         * Przesunięcie względem rozmiarów rodzica. Działa tylko w gdy rodzic jest
         * typu BoxGroup. Ujemne oznacza nieustawione. Jednostką jest procent.
         */
        Geometry::Point const &getTranslate () const { return translate; }

        /**
         * Justowanie.
         */
        int getAlign () const { return align; }

        /**
         * Justowanie.
         */
        void setAlign (int a) { align = a; }

        /**
         * Padding.
         */
        Padding *getPadding () { return padding; }

        /**
         * Padding.
         */
        void setPadding (Padding *p) { padding = p; }

        /**
         * Rozszerz ten obiekt do rozmiarów rodzica.
         */
        bool getExpand () const { return expand; }

        /**
         * Rozszerz ten obiekt do rozmiarów rodzica.
         */
        void setExpand (bool b) { expand = b; }

        /**
         * Zmniejsz ten obiekto do rozmiarów jego zawartości (do rozmiarów AABB jego zawartości).
         */
        bool getShrink () const { return shrink; }

        /**
         * Zmniejsz ten obiekto do rozmiarów jego zawartości (do rozmiarów AABB jego zawartości).
         */
        void setShrink (bool b) { shrink = b; }

/*--------------------------------------------------------------------------*/

        /*
         * @param m Model którego dotyczy request
         * @param origTranslate Aktualne przesunięcie tego modelu.
         * @param w Aktualna wysokość boundingBoxa modelu m
         * @param h Aktualna szerokość boundingBoxa modelu m
         */
        Geometry::Point calculateTranslation (IModel const *m, Geometry::Point const &currentTranslate, double aabbW, double aabbH) const;

private:

        int             p_ (align);
        float           p_ (width);
        float           p_ (height);
        Geometry::Point P_ (translate);
        Padding *       p_ (padding);
        bool            p_ (expand);
        bool            p_ (shrink);

        E_ (BoxGroupProperties)
};

} /* namespace Model */

#	endif /* LAYOUT_H_ */
