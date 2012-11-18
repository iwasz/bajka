/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include "Circle.h"
#include "geometry/Ring.h"

namespace Model {
using namespace boost::geometry;
using namespace Geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

Geometry::AffineMatrix Circle::getMatrix () const
{
        return AffineMatrix (translate + origin, getAngle (), scale + radius, getRotationCenter ());
}

/****************************************************************************/

Geometry::Point Circle::computeCenter () const
{
        return origin;
}

/****************************************************************************/

bool Circle::contains (Point const &p) const
{
        // TODO!
        return true;
}

/****************************************************************************/

G::Box Circle::getBoundingBoxImpl (Geometry::AffineMatrix const &) const
{
        double r = radius * scale;
        double x = translate.x + origin.x;
        double y = translate.y + origin.y;
        return G::Box (x - r, y - r, x + r, y + r);
}


} /* namespace Model */
