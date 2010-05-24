/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef KEYBOARDEVENT_H_
#define KEYBOARDEVENT_H_

#include "IEvent.h"
#include "IObserver.h"

namespace Event {

class KeyboardEvent : public AbstractEvent {
public:

//        enum { PRESSED, RELEASED } Type;

        virtual ~KeyboardEvent () {}

//        Type getType () const { return KEYBOARD_EVENT; }

private:

//        Type type;
//        unsigned int scancode;
//        SDLKey sym;
//        SDLMod mod;
//        unsigned int unicode;

};

/**
 *
 */
struct KeyDownEvent : public KeyboardEvent {
        virtual ~KeyDownEvent () {}
        Type getType () const { return  KEY_DOWN_EVENT; }
        virtual void runObserver (IObserver *o) { o->onKeyDown (static_cast <KeyDownEvent *> (this)); }
};

/**
 *
 */
struct KeyUpEvent : public KeyboardEvent {
        virtual ~KeyUpEvent () {}
        Type getType () const { return  KEY_UP_EVENT; }
        virtual void runObserver (IObserver *o) { o->onKeyUp (static_cast <KeyUpEvent *> (this)); }
};

}

#	endif /* KEYBOARDEVENT_H_ */
