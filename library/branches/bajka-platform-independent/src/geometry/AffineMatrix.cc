/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cmath>
#include "AffineMatrix.h"

namespace Geometry {
using namespace boost::numeric::ublas;

/**
 * Macierz jednostkowa.
 */
const AffineMatrix AffineMatrix::UNITARY;

/****************************************************************************/

AffineMatrix::AffineMatrix () : BaseMatrixType ()
{
        resetIdentity ();
}

/****************************************************************************/

AffineMatrix::AffineMatrix (const AffineMatrix &m) : BaseMatrixType (m) {}

/****************************************************************************/

AffineMatrix::AffineMatrix (Geometry::Point translate, double angle, double scale, Geometry::Point ct) : BaseMatrixType ()
{
	double aRad = angle * M_PI / 180.0;
	double s = scale * sin (aRad);
	double c = scale * cos (aRad);

	operator() (0,0) = c;   operator() (0,1) = -s;   operator() (0,2) = 0;   operator() (0,3) = -c * ct.x + s * ct.y + ct.x + translate.x;
	operator() (1,0) = s;   operator() (1,1) = c;    operator() (1,2) = 0;   operator() (1,3) = -s * ct.x - c * ct.y + ct.y + translate.y;
	operator() (2,0) = 0;   operator() (2,1) = 0;    operator() (2,2) = 1;   operator() (2,3) = 0;
	operator() (3,0) = 0;   operator() (3,1) = 0;    operator() (3,2) = 0;   operator() (3,3) = 1;
}

/****************************************************************************/

void AffineMatrix::move (const Geometry::Point &p)
{
        BaseMatrixType m;

        m (0,0) = 1;   m (0,1) = 0;   m (0,2) = 0;   m (0,3) = p.x;
        m (1,0) = 0;   m (1,1) = 1;   m (1,2) = 0;   m (1,3) = p.y;
        m (2,0) = 0;   m (2,1) = 0;   m (2,2) = 1;   m (2,3) = 0;
        m (3,0) = 0;   m (3,1) = 0;   m (3,2) = 0;   m (3,3) = 1;

        *this = prod (*this, m);
}

/****************************************************************************/

//void AffineMatrix::rotate (double r)
//{
//        //BaseMatrixType m (4, 4);
//        AffineMatrix m;
//
//        double c = cos (r);
//        double s = sin (r);
//
//        m (0,0) = c;   m (0,1) = -s;   m (0,2) = 0;   m (0,3) = 0;
//        m (1,0) = s;   m (1,1) = c;    m (1,2) = 0;   m (1,3) = 0;
//        m (2,0) = 0;   m (2,1) = 0;    m (2,2) = 1;   m (2,3) = 0;
//        m (3,0) = 0;   m (3,1) = 0;    m (3,2) = 0;   m (3,3) = 1;
//
//        //assign (prod (*this, m));
//        *this = prod (*this, m);
//}

/****************************************************************************/

void AffineMatrix::rotate (double r, Geometry::Point const &p)
{
        BaseMatrixType m;

        double c = cos (r);
        double s = sin (r);

        m (0,0) = c;   m (0,1) = -s;   m (0,2) = 0;   m (0,3) = p.x - c * p.x + s * p.y;
        m (1,0) = s;   m (1,1) = c;    m (1,2) = 0;   m (1,3) = p.y - s * p.x - c * p.y;
        m (2,0) = 0;   m (2,1) = 0;    m (2,2) = 1;   m (2,3) = 0;
        m (3,0) = 0;   m (3,1) = 0;    m (3,2) = 0;   m (3,3) = 1;

        //assign (prod (*this, m));
        *this = prod (*this, m);
}

/****************************************************************************/

void AffineMatrix::resize (double w, double h, Geometry::Point const &p)
{
        BaseMatrixType m;

        m (0,0) = w;   m (0,1) = 0;   m (0,2) = 0;   m (0,3) = p.x - w * p.x;
        m (1,0) = 0;   m (1,1) = h;   m (1,2) = 0;   m (1,3) = p.y - h * p.x;
        m (2,0) = 0;   m (2,1) = 0;   m (2,2) = 1;   m (2,3) = 0;
        m (3,0) = 0;   m (3,1) = 0;   m (3,2) = 0;   m (3,3) = 1;

        *this = prod (*this, m);
}

} // nam
