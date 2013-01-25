/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GEOMETRY_BAJKA_POLYGON_H_
#define GEOMETRY_BAJKA_POLYGON_H_

#include <boost/geometry/geometries/polygon.hpp>
#include "Point.h"

namespace Geometry {

/**
 * Skomplikowany poligon, kŧóry składa się z jedego pierścienia (ring) zewnętrznego
 * i zero lub więcej pierścieni wewnętrznych (dziurek).
 */
typedef boost::geometry::model::polygon <Point> Polygon;

} /* namespace Geometry */

// TODO! Nie ma jak zarejestrować! Nie ma makra!

#endif /* POLYGON_H_ */
