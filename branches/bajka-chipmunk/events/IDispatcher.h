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
#include "../events/types/IEvent.h"

namespace Model {
class IModel;
}

namespace Util {
class BajkaApp;
}

namespace Event {

/**
 * Do wysyłania eventów.
 * \ingroup Events
 */
class IDispatcher : public Core::Object {
public:
        virtual ~IDispatcher () {}
        virtual void run (Model::IModel *m, ModelIndex const &modeliIndex) = 0;
        virtual Util::BajkaApp *getApp () = 0;
        virtual void setApp (Util::BajkaApp *a) = 0;

        virtual void setPointerInside (Model::IModel *m) = 0;
        virtual void removePointerInside (Model::IModel *m) = 0;
        virtual bool isPointerInside (Model::IModel *m) const = 0;
};

/**
 * Dla kontenera.
 */
typedef std::list <Ptr <IDispatcher> > DispatcherList;
g_ (DispatcherList)

}

#	endif /* IDISPATCHER_H_ */
