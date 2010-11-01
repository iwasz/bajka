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
#include "IObserver.h"

namespace Event {

/**
 * Event pojawiający się po naciśnięciu "x" na oknie.
 * \ingroup Events
 */
struct QuitEvent : public AbstractEvent {
        virtual ~QuitEvent () {}
        Type getType () const { return QUIT_EVENT; }
        virtual bool runObserver (IObserver *o) { return o->onQuit (static_cast <QuitEvent *> (this)); }
};

}

#	endif /* QUITEVENT_H_ */
