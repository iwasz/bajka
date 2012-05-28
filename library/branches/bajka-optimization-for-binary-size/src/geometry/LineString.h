/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_GEOMETRY_LINESTRING_H_
#define BAJKA_GEOMETRY_LINESTRING_H_

#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/register/linestring.hpp>
#include <variant/Variant.h>
#include <Pointer.h>
#include <string>
#include "Point.h"

namespace Geometry {

/**
 * Otwarty ciąg odcinków.
 */
typedef boost::geometry::model::linestring <Point> LineString;

/**
 * Tworzy LineString z reprezentacji napisowej.
 */
extern Ptr <LineString> stringToLineString (std::string const &p);

/**
 * Tworzy punkt z reprezentacji napisowej, zwraca jako Core::Variant.
 */
extern Core::Variant stringToLineStringVariant (std::string const &p);

} /* namespace Geometry */


#endif /* LINESTRING_H_ */
