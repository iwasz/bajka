/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SEGMENT_H_
#define BAJKA_SEGMENT_H_

#include <boost/geometry/geometries/segment.hpp>
#include "Point.h"

namespace Geometry {

typedef boost::geometry::model::segment <Point> Segment;

} /* namespace Geometry */
#endif /* SEGMENT_H_ */
