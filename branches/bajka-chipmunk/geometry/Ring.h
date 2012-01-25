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
#include "Point.h"

namespace Geometry {

/**
 * Poligon, który nie ma dziurek.
 */
class Ring : public boost::geometry::model::ring <Point> {
public:
        virtual ~Ring () {}
};

} /* namespace Geometry */

#	endif /* RING_H_ */
