/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BaseMatrixType.h"

namespace Geometry {
using namespace boost::numeric::ublas;

/****************************************************************************/

void BaseMatrixType::resetIdentity ()
{
        *this = identity_matrix <double> (4);
}

/****************************************************************************/

void BaseMatrixType::transform (Point *p) const
{
        float x = p->x;
        float y = p->y;

        // Looks odd, but it is like this_matrix (0, 0)
        p->x = (x * operator()(0,0) + y * operator()(0,1) + operator()(0,3));
        p->y = (x * operator()(1,0) + y * operator()(1,1) + operator()(1,3));
}

/****************************************************************************/

Point BaseMatrixType::getTransformed (const Point &p) const
{
        Point tmp (p);
        transform (&tmp);
        return tmp;
}

/****************************************************************************/

void BaseMatrixType::invert ()
{
        invertMatrix (data ().begin (), data ().begin ());
}

/****************************************************************************/

BaseMatrixType BaseMatrixType::getInversed () const
{
        BaseMatrixType tmp = *this;
        tmp.invert ();
        return tmp;
}

/**
 * Implementation teken from MESA.
 * @param m
 * @param invOut
 * @return
 */
bool BaseMatrixType::invertMatrix (const float m[16], float invOut[16])
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

}
