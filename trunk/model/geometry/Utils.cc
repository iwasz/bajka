/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/util/write_dsv.hpp>
#include "Utils.h"

namespace Geometry {
using namespace boost::numeric::ublas;

/****************************************************************************/

void AffineMatrix::resetIdentity ()
{
        *this = identity_matrix <double> (4);
}

/****************************************************************************/

void AffineMatrix::move (const Geometry::Point &p)
{
        AffineMatrixType m (4, 4);

        m (0,0) = 1;   m (0,1) = 0;   m (0,2) = 0;   m (0,3) = p.getX ();
        m (1,0) = 0;   m (1,1) = 1;   m (1,2) = 0;   m (1,3) = p.getY ();
        m (2,0) = 0;   m (2,1) = 0;   m (2,2) = 1;   m (2,3) = 0;
        m (3,0) = 0;   m (3,1) = 0;   m (3,2) = 0;   m (3,3) = 1;

        assign (prod (*this, m));
}

/****************************************************************************/

void AffineMatrix::rotate (double r)
{

}

/****************************************************************************/

void AffineMatrix::resize (double w, double h)
{

}

/****************************************************************************/

void AffineMatrix::transform (Point *p) const
{
        // Looks odd, but it is like this_matrix (0, 0)
        // TODO To jest źle, bo zamiast ostatniego minuisa powinien być plus.
        p->setX (p->getX () * operator()(0,0) + p->getY () * operator()(0,1) - operator()(0,3));
        p->setY (p->getX () * operator()(1,0) + p->getY () * operator()(1,1) - operator()(1,3));
}

/****************************************************************************/

Point AffineMatrix::transform (const Point &p) const
{
        Point tmp (p);
        transform (&tmp);
        return tmp;
}

/****************************************************************************/

Core::String AffineMatrix::toString (unsigned int) const
{

        Core::String s = "AffineMatrix (";
        s += (double)operator()(0,0); s += ", ";
        s += operator()(0,1); s += ", ";
        s += operator()(0,2); s += ", ";
        s += operator()(0,3); s += ", ";

        s += operator()(1,0); s += ", ";
        s += operator()(1,1); s += ", ";
        s += operator()(1,2); s += ", ";
        s += operator()(1,3); s += ", ";

        s += operator()(2,0); s += ", ";
        s += operator()(2,1); s += ", ";
        s += operator()(2,2); s += ", ";
        s += operator()(2,3); s += ", ";

        s += operator()(3,0); s += ", ";
        s += operator()(3,1); s += ", ";
        s += operator()(3,2); s += ", ";
        s += operator()(3,3); s += ")";
        return s;
}

} // nam
