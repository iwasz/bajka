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
#include "geometry/Utils.h"
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

void AbstractModel::setPosition (const Geometry::Point &p)
{
        setMove (p - getMove ());
}

/****************************************************************************/

void AbstractModel::setRotate (double deg)
{
        matrix.rotate (deg * (M_PI / 180.0));
}

/****************************************************************************/

void AbstractModel::setRotate (double deg, const Geometry::Point &p)
{
        matrix.rotate (deg * (M_PI / 180.0), p);
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

void AbstractModel::setRotateRad (double rad, const Geometry::Point &p)
{
        matrix.rotate (rad, p);
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

void AbstractModel::setResize (double w, double h, Geometry::Point const &p)
{
        matrix.resize (w, h, p);
}

/****************************************************************************/

double AbstractModel::getResizeW () const
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
        return p.getX ();
}

/****************************************************************************/

double AbstractModel::getResizeH () const
{
        Point p (0.0, 1.0);
        double tmpX = matrix (0,3);
        double tmpY = matrix (1,3);
        AbstractModel *ptr = const_cast <AbstractModel *> (this);
        ptr->matrix (0,3) = 0.0;
        ptr->matrix (1,3) = 0.0;
        matrix.transform (&p);
        ptr->matrix (0,3) = tmpX;
        ptr->matrix (1,3) = tmpY;
        return p.getY ();
}

/*##########################################################################*/

bool AbstractModel::enclose (const Geometry::Point &p) const
{
        for (AbstractModel::const_iterator i = begin (); i != end (); ++i) {
                if ((*i)->enclose (p)) {
                        return true;
                }
        }

        return false;
}

/****************************************************************************/

// Test tego kiedyś
Box AbstractModel::getBoundingBox () const
{
        Box ret;

        // Jak to zrobić za pomocą std::accumulate?
        for (const_iterator i = begin (); i != end (); ++i) {
                ret = Geometry::getBoundingBox (ret, (*i)->getBoundingBox ());
        }

        return ret;
}

/*##########################################################################*/

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
        return tmpPoint - getOrigin ();
}

/****************************************************************************/

Geometry::Point AbstractModel::modelToScreen (Geometry::Point const &p) const
{
        updateMatrixStack ();
        Point tmpPoint = p;
        matrixStack.transform (&tmpPoint);
        return tmpPoint + getOrigin ();
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
