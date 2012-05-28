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
#include "ReflectionMacros.h"
#include "EventIdex.h"
#include "../events/types/IEvent.h"

namespace Model {
class IModel;
}

namespace Util {
class App;
}

namespace Event {
class PointerInsideIndex;

/**
 * Do wysyłania eventów.
 * \ingroup Events
 */
class IDispatcher : public Core::Object {
public:
        virtual ~IDispatcher () {}

        /**
         * Pobiera kolejne eventy z systemu i przekazuje je do dispatch.
         */
        virtual bool pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex) = 0;

        /**
         * Zwraca true, kiedy event został obsłużony przez grę i nie powinien zostać przekazany do
         * systemu. Ma to znaczenie w androidzie, gdzie aplikacja i system współdzielą eventy.
         */
        virtual bool dispatch (Model::IModel *m, EventIndex const &modeliIndex, PointerInsideIndex *pointerInsideIndex, void *platformDependentData) = 0;
        virtual void reset () = 0;

        virtual Util::App *getApp () = 0;
        virtual void setApp (Util::App *a) = 0;

};

/**
 * Dla kontenera.
 */
typedef std::list <Ptr <IDispatcher> > DispatcherList;
g_ (DispatcherList)

}

#	endif /* IDISPATCHER_H_ */
