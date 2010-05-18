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

namespace Geometry {

/**
 *
 */
typedef boost::geometry::strategy::transform::ublas_transformer
        <boost::geometry::point_2d, boost::geometry::point_2d, 2, 2> UblasTransformer;

/**
 *
 */
struct AffineTransformation : public UblasTransformer {

        typedef UblasTransformer::matrix_type matrix_type;
        matrix_type &matrix () { return m_matrix; }

};


/**
 * Affine matrix type optimised to use with OpenGL.
 */
/*
 * Tu jest podany parametr szablonowy column_major, który mówi o ustawieniu
 * elementów w pamięci (kolumnami, czy wierszami).
 */
typedef boost::numeric::ublas::matrix <double, boost::numeric::ublas::column_major> AffineMatrix;

} // namespace

#	endif /* UTILS_H_ */
