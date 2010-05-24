/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef UTILS_H_
#define UTILS_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/geometry/geometries/cartesian2d.hpp>
#include <boost/geometry/strategies/transform/matrix_transformers.hpp>
#include <stack>
#include <IToStringEnabled.h>

#include "geometry/Point.h"

namespace Geometry {

/**
 * Affine matrix type optimised to use with OpenGL.
 */
/*
 * Tu jest podany parametr szablonowy column_major, który mówi o ustawieniu
 * elementów w pamięci (kolumnami, czy wierszami).
 */
typedef boost::numeric::ublas::matrix <double, boost::numeric::ublas::column_major> AffineMatrixType;

/**
 *
 */
struct AffineMatrix : public AffineMatrixType, public Core::IToStringEnabled {

        AffineMatrix () : AffineMatrixType (4, 4) {}
        AffineMatrix (const AffineMatrix &m) : AffineMatrixType (m) {}

        template<class AE>
        AffineMatrix (const boost::numeric::ublas::matrix_expression<AE> &ae) : AffineMatrixType (ae) {}

/*------transformations-----------------------------------------------------*/

        void resetIdentity ();
        void move (const Geometry::Point &p);
        void rotate (double r);
        void resize (double w, double h);

/*------apply-transformation------------------------------------------------*/

        void transform (Point *) const;
        Point transform (const Point &) const;

/*--------------------------------------------------------------------------*/

        Core::String toString (unsigned int = 0) const;

};

/**
 * Stos - dla eventów.
 */
typedef std::stack <AffineMatrix> AffineMatrixStack;

} // namespace

#	endif /* UTILS_H_ */
