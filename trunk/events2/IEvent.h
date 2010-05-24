/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IEVENT_H_
#define IEVENT_H_

#include <cstddef>

namespace Event {

enum Type {
        MOUSE_MOTION_EVENT      = 0x01,
        BUTTON_PRESS_EVENT      = 0x01 << 1,
        BUTTON_RELEASE_EVENT    = 0x01 << 2,
        TIMER_EVENT             = 0x01 << 3,
        KEY_DOWN_EVENT          = 0x01 << 4,
        KEY_UP_EVENT            = 0x01 << 5,
        QUIT_EVENT              = 0x01 << 6
};

class IObserver;

/**
 * Służy do przekazywania danych dodatkowych - coś takiego jak void *data
 * w niektórych bibliotekach C.
 */
struct IEventContext {
        virtual ~IEventContext () {}
};

/**
 * Typowy visitor-pattern się zrobił.
 */
class IEvent {
public:
        virtual ~IEvent () {}
        virtual Type getType () const = 0;
        // TODO zwracać bool
        virtual void runObserver (IObserver *o) = 0;
        virtual IEventContext *getContext () const = 0;
        virtual void setContext (IEventContext *ctx) = 0;
};

/**
 *
 */
class AbstractEvent : public IEvent {
public:

        AbstractEvent () : context (NULL) {}
        virtual ~AbstractEvent () {}

        IEventContext *getContext () const { return context;}
        void setContext (IEventContext *ctx) { context = ctx; }

private:

        IEventContext *context;
};

}

#	endif /* IEVENT_H_ */
