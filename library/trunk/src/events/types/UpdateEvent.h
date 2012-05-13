/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_UPDATE_EVENT_H_
#define BAJKA_UPDATE_EVENT_H_

#include "IEvent.h"
#include <string>

namespace Event {

/**
 * Event podczas kolejnej iteracji.
 * \ingroup Events
 */
class UpdateEvent : public IEvent {
public:

        UpdateEvent () : deltaMs (0) {}
        virtual ~UpdateEvent () {}

        unsigned int getDeltaMs () const { return deltaMs; }
        void setDeltaMs (unsigned int i) { this->deltaMs = i; }

        Type getType () const { return UPDATE_EVENT; }
        virtual bool runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return true; }

        virtual std::string toString () const { return "UpdateEvent ()"; }

private:

        unsigned int deltaMs;
};

}

#	endif /* TIMEREVENT_H_ */
