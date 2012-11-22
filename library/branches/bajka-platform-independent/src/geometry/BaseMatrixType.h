/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BASEMATRIXTYPE_H_
#define BASEMATRIXTYPE_H_

#include <boost/numeric/ublas/matrix.hpp>
#include "Point.h"

namespace Geometry {

/**
 * Matrix type optimised to use with OpenGL.
 * \ingroup Geometry
 */
/*
 * Tu jest podany parametr szablonowy column_major, który mówi o ustawieniu
 * elementów w pamięci (kolumnami, czy wierszami).
 */
namespace {
typedef boost::numeric::ublas::matrix <float, boost::numeric::ublas::column_major> BaseMatrixType_T;
}

class BaseMatrixType : public BaseMatrixType_T {
public:

        BaseMatrixType () : BaseMatrixType_T (4, 4) { resetIdentity (); }
        BaseMatrixType (const BaseMatrixType &m) : BaseMatrixType_T (m) {}

        template<class AE>
        BaseMatrixType (const boost::numeric::ublas::matrix_expression<AE> &ae) : BaseMatrixType_T (ae) {}

/*--------------------------------------------------------------------------*/

        void resetIdentity ();
        void invert ();
        BaseMatrixType getInversed () const;

/*------apply-transformation------------------------------------------------*/

        void transform (Point *) const;
        Point getTransformed (const Point &) const;

private:

        bool invertMatrix (const float m[16], float invOut[16]);
};

}

#endif /* BASEMATRIXTYPE_H_ */
