/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_UTILS_COMMONS_H_
#define BAJKA_UTILS_COMMONS_H_

#include <Reflection.h>
#include <collection/List.h>
#include <collection/Vector.h>
#include <Pointer.h>

namespace Util {

typedef Reflection::List <int> IntList;
_f (IntList)

typedef Reflection::Vector <int> IntVector;
_f (IntVector)

typedef Reflection::List <double> DoubleList;
_f (DoubleList)

typedef Reflection::Vector <double> DoubleVector;
_f (DoubleVector)

template <typename Op, typename Arg>
struct ConvertPtr_t : public std::unary_function <Arg, typename Op::result_type> {

        ConvertPtr_t (Op const &o) : op (o) {}

        typename Op::result_type operator () (Arg arg) const
        {
                return op (arg.get ());
        }

private:

        Op op;

};

template <typename Arg, typename Op>
ConvertPtr_t <Op, Arg>
ConvertPtr (Op const &o)
{
        return ConvertPtr_t <Op, Arg> (o);
}

}

#	endif /* UTILS_H_ */
