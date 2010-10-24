/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDISPATCHER_H_
#define IDISPATCHER_H_

#include <Object.h>

#include "IObserver.h"
#include "collection/List.h"

namespace Event {

/**
 * Do wysyłania eventów.
 * \ingroup Events
 */
class IDispatcher : public Core::Object {
public:
        virtual ~IDispatcher () {}

        virtual void run () = 0;
        /// Ustawia nową kolekcję obserwatorów.
        virtual void setObservers (Event::ObserverVector const &o) = 0;
        /// Dodaje obserwatora do listy. Bedzie on powiadamiany o ewentach.
        virtual void addObserver (Ptr <IObserver> o) = 0;
        /// Usuwa wszystkie wystąpienia obserwatora z listy.
        virtual void removeObserver (Ptr <IObserver> o) = 0;
};

/**
 * Dla kontenera.
 */
typedef Reflection::List <Ptr <IDispatcher> > DispatcherList;
_f (DispatcherList)

}

#	endif /* IDISPATCHER_H_ */
