/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include "Box.h"
#include "../../geometry/Ring.h"

namespace Model {
using namespace boost::geometry;
using namespace Geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

Geometry::Point Box::computeCenter () const
{
        return Point ((box.ll.x + box.ur.x) / 2.0, (box.ll.y + box.ur.y) / 2.0);
}

/****************************************************************************/

bool Box::contains (Point const &p) const
{
        Ring ring;
        convert (box, ring);

        double aRad = angle * M_PI / 180.0;
        double s = scale * sin (aRad);
        double c = scale * cos (aRad);
        Point ct = getCenter ();

        trans::ublas_transformer <Point, Point, 2, 2> matrix (
                c, -s, -c * ct.x + s * ct.y + ct.x + translate.x,
                s,  c, -s * ct.x - c * ct.y + ct.y + translate.y,
                0,  0,  1
        );

        Ring output;
        boost::geometry::transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

G::Box Box::getBoundingBox () const
{
        G::Box aabb;
        Ring ring;
        convert (box, ring);

        double aRad = angle * M_PI / 180.0;
        double s = scale * sin (aRad);
        double c = scale * cos (aRad);
        Point ct = getCenter ();

        trans::ublas_transformer <Point, Point, 2, 2> matrix (
    		c, -s, -c * ct.x + s * ct.y + ct.x + translate.x,
    		s,  c, -s * ct.x - c * ct.y + ct.y + translate.y,
    		0,  0,  1
        );

        Ring output;
        boost::geometry::transform (ring, output, matrix);
        envelope (output, aabb);
        return aabb;
}


} /* namespace Model */
