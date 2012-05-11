/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_SDL
#include "EventDispatcher.h"
#include "Common.h"
#include "../../../events/PointerInsideIndex.h"
#include "../../../events/EventIdex.h"
#include "OpenGlService.h"

namespace Event {
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace G = Geometry;

void EventDispatcher::pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex)
{
        SDL_Event event;

        while (SDL_PollEvent (&event)) {
                dispatch (m, modeliIndex, pointerInsideIndex, &event);
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
                return updateKeyboardDownEvent (event);

        case SDL_KEYUP:
                return updateKeyboardUpEvent (event);

        case SDL_QUIT:
                return &quitEvent;

        case SDL_ACTIVEEVENT:
                return updateActiveEvent (event);

        case SDL_VIDEORESIZE:
                return updateResizeEvent (event);

        case SDL_VIDEOEXPOSE:
                return &exposeEvent;

        default:
                break;
        }

        return NULL;
}

/****************************************************************************/

KeyboardEvent *EventDispatcher::updateKeyboardUpEvent (SDL_Event *event)
{
        keyUpEvent.setKeyCode (static_cast <KeyCode> (event->key.keysym.sym));
        keyUpEvent.setKeyMod (static_cast <KeyMod> (event->key.keysym.mod));
        return &keyUpEvent;
}

/****************************************************************************/

KeyboardEvent *EventDispatcher::updateKeyboardDownEvent (SDL_Event *event)
{
        keyDownEvent.setKeyCode (static_cast <KeyCode> (event->key.keysym.sym));
        keyDownEvent.setKeyMod (static_cast <KeyMod> (event->key.keysym.mod));
        return &keyDownEvent;
}

/****************************************************************************/

MouseMotionEvent *EventDispatcher::updateMouseMotionEvent (SDL_Event *event)
{
        mouseMotionEvent.setButtons ((unsigned int)event->motion.state);

        int resX2 = app->getConfig ()->getResX ();
        int resY2 = app->getConfig ()->getResY ();

        G::Point p;
        V::OpenGlService::mouseToDisplay (event->button.x, event->button.y, resX2, resY2, &p.x, &p.y);
        mouseMotionEvent.setPosition (p);

#if 0
        std::cerr << event->motion.xrel << ", " << event->motion.yrel << std::endl;
#endif

        // ?
        mouseMotionEvent.setMovement (G::Point (event->motion.xrel, event->motion.yrel));

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

        int resX2 = app->getConfig ()->getResX ();
        int resY2 = app->getConfig ()->getResY ();

        G::Point p;
        V::OpenGlService::mouseToDisplay (event->button.x, event->button.y, resX2, resY2, &p.x, &p.y);
        output->setPosition (p);
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

/****************************************************************************/

Event::ActiveEvent *EventDispatcher::updateActiveEvent (SDL_Event *event)
{
        activeEvent.setActive (event->active.gain);
        activeEvent.setState (static_cast <ActiveState> (event->active.state));
        return &activeEvent;
}

/****************************************************************************/

Event::ResizeEvent *EventDispatcher::updateResizeEvent (SDL_Event *event)
{
        resizeEvent.setWidth (event->resize.w);
        resizeEvent.setHeight (event->resize.h);
        return &resizeEvent;
}

/****************************************************************************/

void EventDispatcher::reset ()
{
        // Discard all pending events
        SDL_Event event;

        while (SDL_PollEvent (&event) > 0)
                ;
}

} // nam

#endif
