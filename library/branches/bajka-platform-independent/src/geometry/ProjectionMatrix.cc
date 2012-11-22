/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cmath>
#include "ProjectionMatrix.h"

namespace Geometry {
using namespace boost::numeric::ublas;

const ProjectionMatrix ProjectionMatrix::UNITARY;

void ProjectionMatrix::setViewport (float left, float right, float bottom, float top)
{
        operator() (0,0) = 2.0 / (right - left);   operator() (0,1) = 0;                    operator() (0,2) = 0;    operator() (0,3) = -(right + left) / (right - left);
        operator() (1,0) = 0;                      operator() (1,1) = 2.0 / (top - bottom); operator() (1,2) = 0;    operator() (1,3) = -(top + bottom) / (top - bottom);
        operator() (2,0) = 0;                      operator() (2,1) = 0;                    operator() (2,2) = -1;   operator() (2,3) = 0;
        operator() (3,0) = 0;                      operator() (3,1) = 0;                    operator() (3,2) = 0;    operator() (3,3) = 1;
}

} // nam
