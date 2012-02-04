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
#include <IToStringEnabled.h>
#include <map>

namespace Model {
class IModel;
}

namespace View {
class IView;
}

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
        QUIT_EVENT              = 0x01 << 6,//!< QUIT_EVENT
        ACTIVE_EVENT            = 0x01 << 7,
        EXPOSE_EVENT            = 0x01 << 8,
        RESIZE_EVENT            = 0x01 << 9,
        MOUSE_OVER_EVENT        = 0x01 << 10,
        MOUSE_OUT_EVENT         = 0x01 << 11,
        EVENT_TERMINATOR        = 0x01 << 12 //!< Do not use.
};

const unsigned int MOUSE_EVENTS = MOUSE_MOTION_EVENT | BUTTON_PRESS_EVENT | BUTTON_RELEASE_EVENT;

/**
 * Typowy visitor-pattern się zrobił.
 * \ingroup Events
 */
class IEvent : public Core::IToStringEnabled {
public:
        virtual ~IEvent () {}

        virtual Type getType () const = 0;
        virtual bool runCallback (Model::IModel *m, View::IView *v, Controller::IController *c) = 0;
};

/**
 * Używane do wyszukiwania modeli pod kątem eventu.
 */
typedef std::multimap <Event::Type, Model::IModel *> ModelIndex;

}

#	endif /* IEVENT_H_ */
