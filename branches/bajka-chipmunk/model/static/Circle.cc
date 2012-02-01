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
#include "../../geometry/Ring.h"

namespace Model {
using namespace boost::geometry;
using namespace Geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

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

G::Box Circle::getBoundingBox () const
{
        double r = radius * getScale ();
        double x = getTranslate ().x + origin.x;
        double y = getTranslate ().y + origin.y;
        return G::Box (x - r, y - r, x + r, y + r);
}


} /* namespace Model */
