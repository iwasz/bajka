/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/algorithms/within.hpp>

#include "AbstractModel.h"
#include "geometry/Point.h"

namespace Model {
using namespace boost::numeric::ublas;
using namespace Geometry;

/****************************************************************************/

AbstractModel::AbstractModel ()
{
        //resetMatrix ();
        matrix.resetIdentity ();
}

/****************************************************************************/

//void AbstractModel::resetMatrix ()
//{
//        // Uzywam macierzy 4x4 żeby zoptymalizowac to dla OpenGL.
//        matrix = identity_matrix <double> (4);
//}

/****************************************************************************/

void AbstractModel::setMove (const Point &p)
{
        matrix.move (p);
}

/****************************************************************************/

void AbstractModel::setRotate (double r)
{
        matrix.rotate (r);
}

/****************************************************************************/

void AbstractModel::setResize (double w, double h)
{
        matrix.resize (w, h);
}

/*##########################################################################*/

bool Box::enclose (const Geometry::Point &p) const
{
        boost::geometry::within (p, *(static_cast <const Geometry::Box *> (this)));
}

/****************************************************************************/

void Box::updateScreenCoords () const
{
        screenCoords = *this;
        matrix.transform (&screenCoords.getLL ());
        matrix.transform (&screenCoords.getUR ());
}

}
