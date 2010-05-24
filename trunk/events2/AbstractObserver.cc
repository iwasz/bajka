/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractObserver.h"
#include "IEvent.h"

namespace Event {

bool AbstractObserver::onEvent (IEvent *event)
{
        if (!acceptEvent (event)) {
                return false;
        }

        event->runObserver (this);
        return true;
}

/****************************************************************************/

inline bool AbstractObserver::acceptEvent (IEvent *event) const
{
        return event->getType () & bitMask;
}

}
