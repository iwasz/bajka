/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef UTILS_H_
#define UTILS_H_

#include <collection/List.h>
#include <collection/Vector.h>

namespace Util {

typedef Reflection::List <int> IntList;
_f (IntList)

typedef Reflection::Vector <int> IntVector;
_f (IntVector)

typedef Reflection::List <double> DoubleList;
_f (DoubleList)

typedef Reflection::Vector <double> DoubleVector;
_f (DoubleVector)

}

#	endif /* UTILS_H_ */
