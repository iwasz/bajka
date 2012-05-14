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

double Box::getWidth () const
{
        updateToViewSizeIf ();
        return box.getWidth ();
}

/****************************************************************************/

double Box::getHeight () const
{
        updateToViewSizeIf ();
        return box.getHeight ();
}

/****************************************************************************/

Geometry::Box Box::getBox () const
{
        updateToViewSizeIf ();
        return box;
}

/****************************************************************************/

Geometry::Point Box::computeCenter () const
{
        updateToViewSizeIf ();
        return makePoint ((box.ll.x + box.ur.x) / 2.0, (box.ll.y + box.ur.y) / 2.0);
}

/****************************************************************************/

bool Box::contains (Point const &p) const
{
        updateToViewSizeIf ();

        Ring ring;
        Ring output;
        convert (box, ring);
        AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

Geometry::Box Box::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
{
        updateToViewSizeIf ();

        G::Box aabb;
        Ring ring;
        Ring output;
        convert (box, ring);
        AffineMatrixTransformer matrix (transformation);
        transform (ring, output, matrix);
        envelope (output, aabb);
        return aabb;
}

} /* namespace Model */
