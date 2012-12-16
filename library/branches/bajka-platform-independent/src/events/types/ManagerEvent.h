/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MANAGER_EVENT_H_
#define BAJKA_MANAGER_EVENT_H_

#include "IEvent.h"

namespace Event {

/**
 * Event zglaszany przez managera.
 */
class ManagerEvent : public IEvent {
public:
        virtual ~ManagerEvent () {}

        Type getType () const { return MANAGER_EVENT; }
        Handling runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return Event::IGNORE; }

        std::string toString () const { return ""; }
};

} /* namespace Event */

#	endif /* EXPOSEEVENT_H_ */
