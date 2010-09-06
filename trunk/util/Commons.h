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

/*
 * Typ ConvertPtr_t
 * \todo Wrzucić do tiliae Pointer.h
 */
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

/**
 * Helper zwracający ConvertPtr_t. Podajemy tylko pierwszy argument szablonowy, który
 * jest typem wejściowym (czyli jakąś kokretyzacją Ptr). Przykład:
 *
 * for_each (begin (), end (), convertPtr <Ptr <IWidget> > (mem_fun (&IWidget::init)));
 *
 * W powyższym przykładzie użyto wywołania convertPtr <Ptr <IWidget> > (op), gdzie op to
 * std::unary_function.
 *
 * convertPtr zwraca funktor, który też jest instancją std::unary_function i oczekuje
 * ragumentu który jest konkretyzacją Ptr. Zamienia taki Ptr na zwykły wskaźnik i podaje
 * go do op.
 *
 * \todo Wrzucić do tiliae Pointer.h
 * \ingroup Util
 */
template <typename Arg, typename Op>
ConvertPtr_t <Op, Arg>
convertPtr (Op const &o)
{
        return ConvertPtr_t <Op, Arg> (o);
}

} // namespace

#	endif /* UTILS_H_ */
