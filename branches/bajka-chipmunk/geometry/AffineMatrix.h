#if 0
/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_UTILS_H_
#define BAJKA_UTILS_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/geometry/strategies/transform/matrix_transformers.hpp>
#include <stack>
#include <IToStringEnabled.h>
#include "Point.h"
#include "Box.h"

namespace Geometry {

/**
 * Affine matrix type optimised to use with OpenGL.
 * \ingroup Geometry
 */
/*
 * Tu jest podany parametr szablonowy column_major, który mówi o ustawieniu
 * elementów w pamięci (kolumnami, czy wierszami).
 */
typedef boost::numeric::ublas::matrix <double, boost::numeric::ublas::column_major> AffineMatrixType;

/**
 * Affine matrix type optimised to use with OpenGL. Dostęp do poszczególnych
 * elementów za pomocą operatora (). Najpierw numer wiersza, potem kolumny.
 * TODO Do osobnego pliku.
 * \ingroup Geometry
 */
class AffineMatrix : public AffineMatrixType, public Core::IToStringEnabled {
public:

        AffineMatrix ();
        AffineMatrix (const AffineMatrix &m);

        template<class AE>
        AffineMatrix (const boost::numeric::ublas::matrix_expression<AE> &ae) : AffineMatrixType (ae) {}

/*------transformations-----------------------------------------------------*/

        void resetIdentity ();
        void inverse ();
        AffineMatrix getInversed () const;

        void move (const Geometry::Point &p);
        void rotate (double r, Geometry::Point const &p = Geometry::Point (0, 0));
        void resize (double w, double h, Geometry::Point const &p = Geometry::Point (0, 0));

/*------apply-transformation------------------------------------------------*/

        void transform (Point *) const;
        Point getTransformed (const Point &) const;

/*--------------------------------------------------------------------------*/

        std::string toString () const;

private:

        bool invertMatrix (const double m[16], double invOut[16]);
};

/**
 * Stos - dla eventów.
 */
typedef std::stack <AffineMatrix> AffineMatrixStack;

/**
 * Bounding box z dwóch innych boxów.
 */
//extern Box getBoundingBox (Box const &b1, Box const &b2);

} // namespace

#	endif /* UTILS_H_ */
#endif
