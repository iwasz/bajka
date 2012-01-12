/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IDISPATCHER_H_
#define BAJKA_IDISPATCHER_H_

#include <Object.h>

namespace Model {
class IModel;
}

namespace Event {

/**
 * Do wysyłania eventów.
 * \ingroup Events
 */
class IDispatcher : public Core::Object {
public:
        virtual ~IDispatcher () {}

        virtual void run (Model::IModel *m) = 0;
//        /// Ustawia nową kolekcję obserwatorów.
//        virtual void setObservers (Event::ObserverVector const &o) = 0;
//        /// Dodaje obserwatora do listy. Bedzie on powiadamiany o ewentach.
//        virtual void addObserver (Ptr <IObserver> o) = 0;
//        /// Usuwa wszystkie wystąpienia obserwatora z listy.
//        virtual void removeObserver (Ptr <IObserver> o) = 0;
};

/**
 * Dla kontenera.
 */
typedef std::list <Ptr <IDispatcher> > DispatcherList;
_g (DispatcherList)

}

#	endif /* IDISPATCHER_H_ */
