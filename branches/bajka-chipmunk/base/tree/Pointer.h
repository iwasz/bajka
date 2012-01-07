/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef POINTER_H_
#define POINTER_H_

//#include <boost/tr1/memory.hpp>
//#define Ptr ::std::tr1::shared_ptr

// TODO Przenieść do Tiliae.
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

#	endif /* POINTER_H_ */
