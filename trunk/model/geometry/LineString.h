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

namespace Model2 {

/**
 * LineString is compatible with boost::geometry::line_string. It represents
 * opened sequence of line segments. It can be used in Tilae.Container using
 * <list class="LineString"> tag.
 */
class LineString : public Reflection::Vector <Point> {
public:

        Core::String toString (unsigned int = 0) const;

};

_f (Model2::LineString)

} // namespa


typedef Model2::LineString __BAJKA_LINE_STRING__;
BOOST_GEOMETRY_REGISTER_LINESTRING (__BAJKA_LINE_STRING__)

#	endif /* LINESTRING_H_ */
