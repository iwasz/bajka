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

Box::Box ()
{
        std::cerr << std::hex << (unsigned long  int)this << std::endl;
}

/****************************************************************************/

Geometry::Point Box::computeCenter () const
{
        return Point ((box.ll.x + box.ur.x) / 2.0, (box.ll.y + box.ur.y) / 2.0);
}

/****************************************************************************/

bool Box::contains (Point const &p) const
{
        Ring ring;
        Ring output;
        convert (box, ring);
        AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

G::Box Box::getBoundingBox () const
{
        G::Box aabb;
        Ring ring;
        Ring output;
        convert (box, ring);
        AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        envelope (output, aabb);
        return aabb;
}

} /* namespace Model */
