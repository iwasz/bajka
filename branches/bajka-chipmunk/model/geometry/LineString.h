/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_LINESTRING_H_
#define BAJKA_LINESTRING_H_

#include <boost/geometry/geometries/register/linestring.hpp>

#include "Point.h"
#include "collection/Vector.h"

namespace Geometry {

/**
 * LineString is compatible with boost::geometry::line_string. It represents
 * opened sequence of line segments. It can be used in Tilae.Container using
 * <list class="LineString"> tag.
 * \ingroup Geometry
 */
class LineString : public Reflection::Vector <Point> {
public:

        Core::String toString (unsigned int = 0) const;

};

_f (Geometry::LineString)

} // namespa


typedef Geometry::LineString __BAJKA_LINE_STRING__;
BOOST_GEOMETRY_REGISTER_LINESTRING (__BAJKA_LINE_STRING__)

#	endif /* LINESTRING_H_ */
