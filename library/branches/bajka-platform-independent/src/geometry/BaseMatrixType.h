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

namespace Geometry {

/**
 * Matrix type optimised to use with OpenGL.
 * \ingroup Geometry
 */
/*
 * Tu jest podany parametr szablonowy column_major, który mówi o ustawieniu
 * elementów w pamięci (kolumnami, czy wierszami).
 */
typedef boost::numeric::ublas::matrix <float, boost::numeric::ublas::column_major> BaseMatrixType;

}

#endif /* BASEMATRIXTYPE_H_ */
