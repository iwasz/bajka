/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/algorithms/within.hpp>
#include "Box.h"

namespace Model {
using namespace boost::numeric::ublas;
using namespace Geometry;

bool Box::enclose (const Geometry::Point &p) const
{
        return boost::geometry::within (p, *(static_cast <const Geometry::Box *> (this))) ||
                        AbstractModel::enclose(p);
}

///****************************************************************************/
//
//void Box::updateScreenCoords () const
//{
//        screenCoords = *this;
//        matrix.transform (&screenCoords.getLL ());
//        matrix.transform (&screenCoords.getUR ());
//}

Geometry::Box Box::getBoundingBox () const
{
        Box b = *this;
        matrix.transform (&b.getLL ());
        matrix.transform (&b.getUR ());
        Box ret;

        ret.setX1 (std::min (b.getX1 (), b.getX2 ()));
        ret.setY1 (std::min (b.getY1 (), b.getY2 ()));
        ret.setX2 (std::max (b.getX1 (), b.getX2 ()));
        ret.setY2 (std::max (b.getY1 (), b.getY2 ()));

        return Geometry::getBoundingBox (ret, AbstractModel::getBoundingBox ());
}

}
