/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IEVENT_H_
#define BAJKA_IEVENT_H_

#include <cstddef>
#include "../controller/IController.h"

/**
 * Eventy.
 */
namespace Event {

/**
 * Typ eventu.
 * \ingroup Events
 */
enum Type {
        MOUSE_MOTION_EVENT      = 0x01,     //!< MOUSE_MOTION_EVENT
        BUTTON_PRESS_EVENT      = 0x01 << 1,//!< BUTTON_PRESS_EVENT
        BUTTON_RELEASE_EVENT    = 0x01 << 2,//!< BUTTON_RELEASE_EVENT
        TIMER_EVENT             = 0x01 << 3,//!< TIMER_EVENT
        KEY_DOWN_EVENT          = 0x01 << 4,//!< KEY_DOWN_EVENT
        KEY_UP_EVENT            = 0x01 << 5,//!< KEY_UP_EVENT
        QUIT_EVENT              = 0x01 << 6 //!< QUIT_EVENT
};

/**
 * Służy do przekazywania danych dodatkowych - coś takiego jak void *data
 * w niektórych bibliotekach C.
 * \ingroup Events
 */
struct IEventContext {
        virtual ~IEventContext () {}
};

/**
 * Typowy visitor-pattern się zrobił.
 * \ingroup Events
 */
class IEvent {
public:
        virtual ~IEvent () {}

        virtual Type getType () const = 0;
        virtual bool runCallback (Controller::IController *c) = 0;

//        virtual IEventContext *getContext () const = 0;
//        virtual void setContext (IEventContext *ctx) = 0;
};

/**
 * Implementuje powtarzalne metody interfejsu IEvent.
 * \ingroup Events
 */
class AbstractEvent : public IEvent {
public:

        AbstractEvent () : context (NULL) {}
        virtual ~AbstractEvent () {}

//        IEventContext *getContext () const { return context;}
//        void setContext (IEventContext *ctx) { context = ctx; }

private:

        IEventContext *context;
};

}

#	endif /* IEVENT_H_ */
