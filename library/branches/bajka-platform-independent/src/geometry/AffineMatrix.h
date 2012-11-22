/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_UTILSAFFINE_MATRIX_H_
#define BAJKA_UTILSAFFINE_MATRIX_H_

#include <boost/geometry/strategies/transform/matrix_transformers.hpp>
#include <vector>
#include "BaseMatrixType.h"

namespace Geometry {

/**
 * Affine matrix type optimised to use with OpenGL. Dostęp do poszczególnych
 * elementów za pomocą operatora (). Najpierw numer wiersza, potem kolumny.
 * \ingroup Geometry
 */
class AffineMatrix : public BaseMatrixType {
public:

        AffineMatrix ();
        AffineMatrix (const AffineMatrix &m);
        AffineMatrix (Geometry::Point translate, double angle, double scale, Geometry::Point center);

        template<class AE>
        AffineMatrix (const boost::numeric::ublas::matrix_expression<AE> &ae) : BaseMatrixType (ae) {}

/*------transformations-----------------------------------------------------*/

        void move (const Geometry::Point &p);
        void rotate (double r, Geometry::Point const &p = ZERO_POINT);
        void resize (double w, double h, Geometry::Point const &p = ZERO_POINT);

        static const AffineMatrix UNITARY;
};

typedef std::vector <AffineMatrix> AffineMatrixVector;

/****************************************************************************/

/**
 * Transformer dla boost::geomoetry.
 */
class AffineMatrixTransformer {
public :

    inline AffineMatrixTransformer (AffineMatrix const& matrix) : m_matrix(matrix) {}

    inline bool apply (Geometry::Point const& p1, Geometry::Point &p2) const
    {
    	p2 = p1;
    	m_matrix.transform (&p2);
        return true;
    }

    AffineMatrix const &matrix() const { return m_matrix; }

protected:

    AffineMatrix m_matrix;
};

} // namespace

#	endif /* UTILS_H_ */
