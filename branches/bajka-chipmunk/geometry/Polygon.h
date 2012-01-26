/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_POLYGON_H_
#define BAJKA_POLYGON_H_

#include <boost/geometry/geometries/polygon.hpp>
#include "Point.h"

namespace Geometry {

struct Polygon : public boost::geometry::model::polygon <Point> {
};

} /* namespace Geometry */

// TODO! Nie ma jak zarejestrować! Nie ma makra!

#endif /* POLYGON_H_ */
