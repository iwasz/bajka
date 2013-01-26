/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SVGGEOMETRY_H_
#define SVGGEOMETRY_H_

#include "util/ReflectionMacros.h"

namespace Container {
class BeanFactoryContainer;
}

namespace Geometry {

/**
 * Ładuje obiekty geometryczne (te z namespace Geometry::) do kontenera. Ustawia je jako singletony
 * zewnętrzne o nazwach takich jak nazwy w SVG.
 */
class SvgGeometryFactory {
public:
        C__ (void)

        /**
         * Kasuje załadowane singletony z pamięci.
         */
        ~SvgGeometryFactory ();

        /**
         * ładuje z pliku i ustawia do kontenera jako singletony.
         */
        m_ (setFile) void setFile (std::string const &s);
private:
        Container::BeanFactoryContainer *p_ (cont);
        Core::VariantMap loadedObjects;
        E_ (SvgGeometryFactory)
};

} /* namespace Geometry */
#endif /* SVGGEOMETRY_H_ */
