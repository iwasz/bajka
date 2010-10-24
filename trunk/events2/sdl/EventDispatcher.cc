/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Common.h"
#include <Foreach.h>

#include "EventDispatcher.h"

using namespace Event;

namespace Sdl {

void EventDispatcher::init ()
{
        ASSERT (config, "config == NULL @ EventDispatcher::init.");
        resX2 = config->getResX () / 2;
        resY2 = config->getResY () / 2;
}

/****************************************************************************/

void EventDispatcher::addObserver (Ptr <IObserver> o)
{
        observers.push_back (o);
}

/****************************************************************************/

void EventDispatcher::removeObserver (Ptr <IObserver> o)
{
        observers.erase (std::remove (observers.begin (), observers.end (), o), observers.end ());
}

/****************************************************************************/

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
        // Run inherited and overloaded methods.
        if (event->type == SDL_MOUSEMOTION) {
                for (Event::ObserverVector::iterator i = observers.begin (); i != observers.end (); ++i) {
                        (*i)->onEvent (updateMouseMotionEvent (event));
                }
        }

        if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
                for (Event::ObserverVector::iterator i = observers.begin (); i != observers.end (); ++i) {
                        (*i)->onEvent (updateMouseButtonEvent (event));
                }
        }

        if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
                for (Event::ObserverVector::iterator i = observers.begin (); i != observers.end (); ++i) {
                        (*i)->onEvent (updateKeyboardEvent (event));
                }
        }
}

/****************************************************************************/

KeyboardEvent *EventDispatcher::updateKeyboardEvent (SDL_Event *event)
{
        // TODO Implement!
//        return keyboardEvent;
        return &keyUpEvent;
}

/****************************************************************************/

MouseMotionEvent *EventDispatcher::updateMouseMotionEvent (SDL_Event *event)
{
        mouseMotionEvent.setButtons ((unsigned int)event->motion.state);
        mouseMotionEvent.setPosition (
                        Geometry::Point (
                                        event->motion.x - resX2,
                                        -event->motion.y + resY2));

        mouseMotionEvent.setMovement (Geometry::Point (event->motion.xrel, event->motion.yrel));
        return &mouseMotionEvent;
}

/****************************************************************************/

MouseButtonEvent *EventDispatcher::updateMouseButtonEvent (SDL_Event *event)
{
        return (event->button.type == SDL_MOUSEBUTTONDOWN) ?
                        (updateMouseButtonEventImpl (&buttonPressEvent, event)) :
                        (updateMouseButtonEventImpl (&buttonReleaseEvent, event));
}

/*--------------------------------------------------------------------------*/

MouseButtonEvent *EventDispatcher::updateMouseButtonEventImpl (MouseButtonEvent *output, SDL_Event *event)
{
        output->setButton (translateMouseButton (event));
        output->setPosition (
                        Geometry::Point (
                                        event->button.x - resX2,
                                        -event->button.y + resY2));

        return output;
}

/*--------------------------------------------------------------------------*/

MouseButton EventDispatcher::translateMouseButton (SDL_Event *event)
{
        switch (event->button.button) {
        case SDL_BUTTON_MIDDLE:
                return CENTER;

        case SDL_BUTTON_RIGHT:
                return RIGHT;

        case 4:
                return BUTTON4;

        case 5:
                return BUTTON5;

        case 6:
                return BUTTON6;

        case 7:
                return BUTTON7;

        case 8:
                return BUTTON8;

        default:
        case SDL_BUTTON_LEFT:
                return LEFT;
        }
}

} // nam
