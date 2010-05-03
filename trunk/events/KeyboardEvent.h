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

namespace Events {

class KeyboardEvent : public IEvent {
public:

        enum { PRESSED, RELEASED } Type;

        virtual ~KeyboardEvent () {}

private:

//        Type type;
//        unsigned int scancode;
//        SDLKey sym;
//        SDLMod mod;
//        unsigned int unicode;

};

}

#	endif /* KEYBOARDEVENT_H_ */
