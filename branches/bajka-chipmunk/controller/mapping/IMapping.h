/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMAPPING_H_
#define IMAPPING_H_

#include <Object.h>
#include <Pointer.h>

namespace Controller {
// Forward
template <typename T> struct ISequence;

/**
 * Mediator.
 * Mediator pomiędzy obiektem ISequence, a jakimś dowolnym innym obiektem.
 * Podczas gdy ISequence generuje jakieś proste wartości, konkretne klasy tego
 * interfejsu mapują te wartości na coś użytecznego. Na przykład uruchamiają
 * metodę Model::IModel::setMove etc.
 *
 * Nie deklaruję tutaj metod ustawiających ISequence, ponieważ nie chcę robić z
 * tego interfejsu szablonu. Tutaj wystarczająca jest metoda IMapping::run.
 * \ingroup Mapping
 */
class IMapping : public Core::Object {
public:
        virtual ~IMapping () {}
        virtual void run () = 0;

};

}

#	endif /* IMAPPING_H_ */
