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

AffineMatrix::AffineMatrix () : BaseMatrixType (4, 4)
{
        resetIdentity ();
}

/****************************************************************************/

AffineMatrix::AffineMatrix (const AffineMatrix &m) : BaseMatrixType (m) {}

/****************************************************************************/

AffineMatrix::AffineMatrix (Geometry::Point translate, double angle, double scale, Geometry::Point ct) : BaseMatrixType (4, 4)
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

void AffineMatrix::resetIdentity ()
{
        *this = identity_matrix <double> (4);
}

/****************************************************************************/

void AffineMatrix::move (const Geometry::Point &p)
{
        BaseMatrixType m (4, 4);

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
        AffineMatrix m;

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
        BaseMatrixType m (4, 4);

        m (0,0) = w;   m (0,1) = 0;   m (0,2) = 0;   m (0,3) = p.x - w * p.x;
        m (1,0) = 0;   m (1,1) = h;   m (1,2) = 0;   m (1,3) = p.y - h * p.x;
        m (2,0) = 0;   m (2,1) = 0;   m (2,2) = 1;   m (2,3) = 0;
        m (3,0) = 0;   m (3,1) = 0;   m (3,2) = 0;   m (3,3) = 1;

        *this = prod (*this, m);
}

/****************************************************************************/

void AffineMatrix::transform (Point *p) const
{
        double x = p->x;
        double y = p->y;

        // Looks odd, but it is like this_matrix (0, 0)
        p->x = (x * operator()(0,0) + y * operator()(0,1) + operator()(0,3));
        p->y = (x * operator()(1,0) + y * operator()(1,1) + operator()(1,3));
}

/****************************************************************************/

Point AffineMatrix::getTransformed (const Point &p) const
{
        Point tmp (p);
        transform (&tmp);
        return tmp;
}

/****************************************************************************/

std::string AffineMatrix::toString () const
{
        std::string s = "AffineMatrix (";

        typedef BaseMatrixType::array_type::const_iterator Iterator;
        for (Iterator i = data ().begin ();;) {

                s += boost::lexical_cast <std::string> (*i);

                if (++i == data ().end ()) {
                        break;
                }

                s += ",";
        }

        return s + ")";
}

/****************************************************************************/

void AffineMatrix::inverse ()
{
        invertMatrix (data ().begin (), data ().begin ());
}

/****************************************************************************/

AffineMatrix AffineMatrix::getInversed () const
{
        AffineMatrix tmp = *this;
        tmp.inverse ();
        return tmp;
}

/**
 * Implementation teken from MESA.
 * @param m
 * @param invOut
 * @return
 */
bool AffineMatrix::invertMatrix (const double m[16], double invOut[16])
{
        double inv[16], det;
        int i;

        inv[0]  =   m[5] * m[10] * m[15] - m[5] * m[11] * m [14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
        inv[4]  =  -m[4] * m[10] * m[15] + m[4] * m[11] * m [14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
        inv[8]  =   m[4] * m[9]  * m[15] - m[4] * m[11] * m [13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
        inv[12] =  -m[4] * m[9]  * m[14] + m[4] * m[10] * m [13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
        inv[1]  =  -m[1] * m[10] * m[15] + m[1] * m[11] * m [14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
        inv[5]  =   m[0] * m[10] * m[15] - m[0] * m[11] * m [14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
        inv[9]  =  -m[0] * m[9]  * m[15] + m[0] * m[11] * m [13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
        inv[13] =   m[0] * m[9]  * m[14] - m[0] * m[10] * m [13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
        inv[2]  =   m[1] * m[6]  * m[15] - m[1] * m[7]  * m [14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] -  m[13] * m[3] * m[6];
        inv[6]  =  -m[0] * m[6]  * m[15] + m[0] * m[7]  * m [14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] +  m[12] * m[3] * m[6];
        inv[10] =   m[0] * m[5]  * m[15] - m[0] * m[7]  * m [13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] -  m[12] * m[3] * m[5];
        inv[14] =  -m[0] * m[5]  * m[14] + m[0] * m[6]  * m [13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] +  m[12] * m[2] * m[5];
        inv[3]  =  -m[1] * m[6]  * m[11] + m[1] * m[7]  * m [10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9]  * m[2] * m[7] +  m[9]  * m[3] * m[6];
        inv[7]  =   m[0] * m[6]  * m[11] - m[0] * m[7]  * m [10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8]  * m[2] * m[7] -  m[8]  * m[3] * m[6];
        inv[11] =  -m[0] * m[5]  * m[11] + m[0] * m[7]  * m [9] +  m[4] * m[1] * m[11] - m[4] * m[3] * m[9] -  m[8]  * m[1] * m[7] +  m[8]  * m[3] * m[5];
        inv[15] =   m[0] * m[5]  * m[10] - m[0] * m[6]  * m [9] -  m[4] * m[1] * m[10] + m[4] * m[2] * m[9] +  m[8]  * m[1] * m[6] -  m[8]  * m[2] * m[5];

        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        if (det == 0) {
                return false;
        }

        det = 1.0 / det;

        for (i = 0; i < 16; i++) {
                invOut[i] = inv[i] * det;
        }

        return true;
}

} // nam
