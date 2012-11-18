/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_UTIL_PRJECTION_MATRIX_H_
#define BAJKA_UTIL_PRJECTION_MATRIX_H_

#include "BaseMatrixType.h"
#include <vector>
#include "Point.h"
#include "Box.h"

namespace Geometry {

/**
 * Do shaderów.
 * \ingroup Geometry
 */
class ProjectionMatrix : public BaseMatrixType {
public:

        ProjectionMatrix () : BaseMatrixType (4, 4) {}
        void setViewport (float left, float right, float top, float bottom);

};

} // namespace

#	endif /* UTILS_H_ */
