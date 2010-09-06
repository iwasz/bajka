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

/****************************************************************************/

Geometry::AffineMatrix const &AbstractModel::updateMatrixStack () const
{
        // TODO Tu można sporo zoptymalizować kiedyś.
        /*
         * UWAGA. Tu jest const_cast, ponieważ ta metoda ma działac "w tle"
         * i po prostu musi być >>const<<.
         */
        Model::IModel *parent = const_cast <AbstractModel *> (this)->getParent ();

        if (parent) {
                matrixStack = parent->updateMatrixStack ();
                boost::numeric::ublas::prod (matrixStack, matrix);
        }
        else {
                matrixStack = matrix;
        }
}

/****************************************************************************/

Geometry::Point const &AbstractModel::screenToModel (Geometry::Point const &p) const
{
        updateMatrixStack ();
        matrixStack.inverse ();
        tmpPoint = p;
        matrixStack.transform (&tmpPoint);
        return tmpPoint;
}

/****************************************************************************/

Geometry::Point const &AbstractModel::modelToScreen (Geometry::Point const &p) const
{
        updateMatrixStack ();
        tmpPoint = p;
        matrixStack.transform (&tmpPoint);
        return tmpPoint;
}

}
