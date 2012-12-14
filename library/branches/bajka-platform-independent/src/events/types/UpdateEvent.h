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

        UpdateEvent () : deltaMs (0), autoPause (false) {}
        virtual ~UpdateEvent () {}

        uint32_t  getDeltaMs () const { return deltaMs; }
        void setDeltaMs (uint32_t  i) { this->deltaMs = i; }

        Type getType () const { return UPDATE_EVENT; }
        virtual bool runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return true; }

        bool getAutoPause () const { return autoPause; }
        void setAutoPause (bool autoPause) { this->autoPause = autoPause; }

        virtual std::string toString () const { return "UpdateEvent ()"; }

private:

        uint32_t deltaMs;
        bool autoPause;
};

}

#	endif /* TIMEREVENT_H_ */
