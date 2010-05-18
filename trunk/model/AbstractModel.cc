/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractModel.h"
#include "geometry/Point.h"

namespace Model {
using namespace boost::numeric::ublas;
using namespace Geometry;

/****************************************************************************/

AbstractModel::AbstractModel ()
{
        resetMatrix ();
}

/****************************************************************************/

void AbstractModel::resetMatrix ()
{
        // Uzywam macierzy 4x4 żeby zoptymalizowac to dla OpenGL.
        matrix = identity_matrix <double> (4);
}

/****************************************************************************/

void AbstractModel::setMove (const Point &p)
{
        AffineMatrix m (4, 4);

        m (0,0) = 1;   m (0,1) = 0;   m (0,2) = 0;   m (0,3) = p.getX ();
        m (1,0) = 0;   m (1,1) = 1;   m (1,2) = 0;   m (1,3) = p.getY ();
        m (2,0) = 0;   m (2,1) = 0;   m (2,2) = 1;   m (2,3) = 0;
        m (3,0) = 0;   m (3,1) = 0;   m (3,2) = 0;   m (3,3) = 1;

        matrix = prod (matrix, m);
}

/****************************************************************************/

void AbstractModel::setRotate (double r)
{

}

/****************************************************************************/

void AbstractModel::setResize (double w, double h)
{

}

}
