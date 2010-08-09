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

//bool Box::enclose (const Geometry::Point &p) const
//{
//        return boost::geometry::within (p, *(static_cast <const Geometry::Box *> (this)));
//}
//
///****************************************************************************/
//
//void Box::updateScreenCoords () const
//{
//        screenCoords = *this;
//        matrix.transform (&screenCoords.getLL ());
//        matrix.transform (&screenCoords.getUR ());
//}

}
