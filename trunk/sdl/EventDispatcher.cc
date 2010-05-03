/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Foreach.h>

#include "EventDispatcher.h"
#include "Common.h"

using namespace Events;

namespace Sdl {

void EventDispatcher::run (SDL_Event *event)
{
        // Run inherited and overloaded methods.
        if (event->type == SDL_MOUSEMOTION) {
                AbstractObservable <MouseMotionEvent>::notifyObservers (updateMouseMotionEvent (event));
        }

        if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
                AbstractObservable <MouseButtonEvent>::notifyObservers (updateMouseButtonEvent (event));
        }

        if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
                AbstractObservable <KeyboardEvent>::notifyObservers (updateKeyboardEvent (event));
        }
}

/****************************************************************************/

const KeyboardEvent &EventDispatcher::updateKeyboardEvent (SDL_Event *event)
{
        // TODO Implement!
        return keyboardEvent;
}

/****************************************************************************/

const MouseMotionEvent &EventDispatcher::updateMouseMotionEvent (SDL_Event *event)
{
        // TODO Implement!
        MouseButton btn = static_cast <MouseButton> (event->motion.state & SDL_BUTTON (1));
        mouseMotionEvent.setButton (btn);
        mouseMotionEvent.setPosition (Model::Point (event->motion.x, event->motion.y));
        mouseMotionEvent.setMovement (Model::Point (event->motion.xrel, event->motion.yrel));
        return mouseMotionEvent;
}

/****************************************************************************/

const MouseButtonEvent &EventDispatcher::updateMouseButtonEvent (SDL_Event *event)
{
        MouseButtonEvent::Type t = (event->button.type == SDL_MOUSEBUTTONDOWN) ? (MouseButtonEvent::DOWN) : (MouseButtonEvent::UP);
        MouseButton btn;

        switch (event->button.button) {
        case SDL_BUTTON_MIDDLE:
                btn = CENTER;
                break;

        case SDL_BUTTON_RIGHT:
                btn = RIGHT;
                break;

        default:
        case SDL_BUTTON_LEFT:
                btn = LEFT;
                break;

        }

        mouseButtonEvent.setType (t);
        mouseButtonEvent.setButton (btn);
        mouseButtonEvent.setPosition (Model::Point (event->button.x, event->button.y));
        return mouseButtonEvent;
}

} // nam
