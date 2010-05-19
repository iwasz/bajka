/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IEVENT_H_
#define IEVENT_H_

namespace Event {

enum Type {
        MOUSE_MOTION_EVENT      = 0x01,
        MOUSE_BUTTON_EVENT      = 0x01 << 1,
        TIMER_EVENT             = 0x01 << 2,
        KEYBOARD_EVENT          = 0x01 << 3
};

/**
 *
 */
class IEvent {
public:
        virtual ~IEvent () {}
        virtual Type getType () const = 0;
};

}

#	endif /* IEVENT_H_ */
