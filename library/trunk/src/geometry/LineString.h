/*
 * LineString.h
 *
 *  Created on: Jan 26, 2012
 *      Author: iwasz
 */

#ifndef BAJKA_LINESTRING_H_
#define BAJKA_LINESTRING_H_

#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/register/linestring.hpp>
#include "Point.h"

namespace Geometry {

/**
 * Otwarty ciąg odcinków.
 */
struct LineString : public boost::geometry::model::linestring <Point> {
};

} /* namespace Geometry */

BOOST_GEOMETRY_REGISTER_LINESTRING (Geometry::LineString);

#endif /* LINESTRING_H_ */
