/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_GEOM_RING_H_
#define BAJKA_GEOM_RING_H_

#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/register/ring.hpp>
#include "Point.h"

namespace Geometry {

/**
 * Krzywa, zamknięty ciąg odcinków. Może być wklęsły, może być
 * wypukły, ale odcinki nie mogą się przecinać. Nie ma powierzchni.
 */
//struct Ring : public boost::geometry::model::ring <Point> {
//
//    inline Ring () : boost::geometry::model::ring <Point> () {}
//
//    template <typename Iterator>
//    inline Ring (Iterator begin, Iterator end) : boost::geometry::model::ring <Point> (begin, end) {}
//
//};

typedef boost::geometry::model::ring <Point> Ring;

} /* namespace Geometry */

//BOOST_GEOMETRY_REGISTER_RING(Geometry::Ring)

#	endif /* RING_H_ */
