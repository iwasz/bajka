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
};

/**
 * Dla kontenera.
 */
typedef std::list <Ptr <IDispatcher> > DispatcherList;
g_ (DispatcherList)

}

#	endif /* IDISPATCHER_H_ */
