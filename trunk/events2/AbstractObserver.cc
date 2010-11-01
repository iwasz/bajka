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
        if (getActive () && !acceptEvent (event)) {
                return false;
        }

        return event->runObserver (this);
}

/****************************************************************************/

inline bool AbstractObserver::acceptEvent (IEvent *event) const
{
        return event->getType () & bitMask;
}

}
