/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#include <chipmunk.h>
#include "geometry/AffineMatrix.h"
#include "Shape.h"
#include "Body.h"
#include "util/Exceptions.h"

namespace Model {

Shape::~Shape ()
{
        cpShapeFree (shape);
}

} /* namespace Model */
#endif
