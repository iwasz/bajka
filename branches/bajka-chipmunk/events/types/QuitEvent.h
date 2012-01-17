/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef QUITEVENT_H_
#define QUITEVENT_H_

#include "IEvent.h"

namespace Event {

/**
 * Event pojawiający się po naciśnięciu "x" na oknie.
 * \ingroup Events
 */
struct QuitEvent : public IEvent {
        virtual ~QuitEvent () {}
        Type getType () const { return QUIT_EVENT; }
        virtual bool runCallback (Controller::IController *c) { return c->onQuit (static_cast <QuitEvent *> (this)); }
        virtual std::string toString () const { return "QuitEvent ()"; }
};

}

#	endif /* QUITEVENT_H_ */
