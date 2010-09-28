/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/algorithms/within.hpp>
#include <boost/functional.hpp>
#include <functional>
#include <cmath>

#include "AbstractModel.h"
#include "geometry/Point.h"
#include "Commons.h"

namespace Model {
using namespace boost::numeric::ublas;
using namespace Geometry;
using namespace Util;
using namespace boost;
using namespace std;

/****************************************************************************/

AbstractModel::AbstractModel () : upToDate (false), alwaysUpdate (false)
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

Point AbstractModel::getMove () const
{
        return Point (matrix (0,3), matrix (1,3));
}

/****************************************************************************/

void AbstractModel::setRotate (double deg)
{
        matrix.rotate (deg * (M_PI / 180.0));
}

/****************************************************************************/

double AbstractModel::getRotate () const
{
        double ret = getRotateRad () * (180.0 / M_PI);
        return (ret < 0) ? (ret + 360) : ret;
}

/****************************************************************************/

void AbstractModel::setRotateRad (double rad)
{
        matrix.rotate (rad);
}

/****************************************************************************/

double AbstractModel::getRotateRad () const
{
        Point p (1.0, 0.0);
        double tmpX = matrix (0,3);
        double tmpY = matrix (1,3);
        AbstractModel *ptr = const_cast <AbstractModel *> (this);
        ptr->matrix (0,3) = 0.0;
        ptr->matrix (1,3) = 0.0;
        matrix.transform (&p);
        ptr->matrix (0,3) = tmpX;
        ptr->matrix (1,3) = tmpY;
        return atan2 (p.getX (), p.getY ());
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

Geometry::Point AbstractModel::screenToModel (Geometry::Point const &p) const
{
        updateMatrixStack ();
        matrixStack.inverse ();
        Point tmpPoint = p;
        matrixStack.transform (&tmpPoint);
        return tmpPoint;
}

/****************************************************************************/

Geometry::Point AbstractModel::modelToScreen (Geometry::Point const &p) const
{
        updateMatrixStack ();
        Point tmpPoint = p;
        matrixStack.transform (&tmpPoint);
        return tmpPoint;
}

/****************************************************************************/

void AbstractModel::update ()
{
        if (!upToDate || alwaysUpdate) {
            upToDate = true;
            doUpdate ();
        }
}

}
