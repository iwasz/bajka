/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "EventDispatcher.h"
#include "Common.h"

using namespace Event;

namespace Sdl {
namespace M = Model;
namespace V = View;
namespace C = Controller;

void EventDispatcher::init ()
{
        resX2 = config->getResX () / 2;
        resY2 = config->getResY () / 2;
}

/****************************************************************************/

static void runRec (Model::IModel *m, Event::IEvent *e)
{
        C::IController *c;
        bool skipChildren = false;

        if ((c = m->getController ())) {
                if (e && e->getType () & c->getEventMask ()) {
                        e->runCallback (m->getController ());
                }
                else {
                        skipChildren = true;
                }
        }

        if (!skipChildren) {
                std::for_each (m->begin (), m->end (), boost::bind (runRec, _1, e));
        }
}

/****************************************************************************/

void EventDispatcher::run (Model::IModel *m)
{
        SDL_Event event;

        while (SDL_PollEvent (&event)) {
                Event::IEvent *e = translate (&event);

                if (e) {
                        runRec (m, e);
                }
        }
}

/****************************************************************************/

Event::IEvent *EventDispatcher::translate (SDL_Event *event)
{
        switch (event->type) {
        case SDL_MOUSEMOTION:
                return updateMouseMotionEvent (event);

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
                return updateMouseButtonEvent (event);

        case SDL_KEYDOWN:
        case SDL_KEYUP:
                return updateKeyboardEvent (event);

        case SDL_QUIT:
                return &quitEvent;

        default:
                break;
        }

        return NULL;
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
