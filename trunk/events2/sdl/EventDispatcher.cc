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

using namespace Event;

namespace Sdl {

void EventDispatcher::run ()
{
        SDL_Event event;

        while (SDL_PollEvent (&event)) {
                translate (&event);

                // TODO Wywalić to i jakoś to rozwiązać inaczej.
                if (event.type == SDL_QUIT) {
                        exit (0);
                }
                if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                                exit (0);
                        }
                }
        }
}

/****************************************************************************/

void EventDispatcher::translate (SDL_Event *event)
{
        if (!observer) {
                return;
        }

        // Run inherited and overloaded methods.
        if (event->type == SDL_MOUSEMOTION) {
                observer->onEvent (updateMouseMotionEvent (event));
        }

        if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
                observer->onEvent (updateMouseButtonEvent (event));
        }

        if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
                observer->onEvent (updateKeyboardEvent (event));
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
        mouseMotionEvent.setPosition (Geometry::Point (event->motion.x, event->motion.y));
        mouseMotionEvent.setMovement (Geometry::Point (event->motion.xrel, event->motion.yrel));
        return mouseMotionEvent;
}

/****************************************************************************/

const MouseButtonEvent &EventDispatcher::updateMouseButtonEvent (SDL_Event *event)
{
        MouseButtonEvent::Press t = (event->button.type == SDL_MOUSEBUTTONDOWN) ? (MouseButtonEvent::DOWN) : (MouseButtonEvent::UP);
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

        mouseButtonEvent.setPress (t);
        mouseButtonEvent.setButton (btn);
        mouseButtonEvent.setPosition (Geometry::Point (event->button.x, event->button.y));
        return mouseButtonEvent;
}

} // nam
