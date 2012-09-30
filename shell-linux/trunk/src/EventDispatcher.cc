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
#include "events/PointerInsideIndex.h"
#include "events/EventIdex.h"
#include "events/types/IEvent.h"
#include "OpenGlService.h"
#include "model/IGroup.h"
#include "Platform.h"
#include "util/IShell.h"
#include "util/Config.h"

namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace G = Geometry;
using namespace Event;

/****************************************************************************/

bool EventDispatcher::dispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex, SDL_Event *sdlEvent)
{
        Event::IEvent *e = translate (sdlEvent);
        bool eventHandled = false;

        if (!e) {
                return eventHandled;
        }

        Event::Type type = e->getType();

        if (type & MOUSE_EVENTS) {
                MouseEvent *mev = static_cast <MouseEvent *> (e);
                G::Point const &p = mev->getPosition ();

/**
 * Smartfony nie generują czegoś takiego jak event on mouseOver i on mouseOut.
 */
#ifndef USE_TOUCH_SCREEN
                if (type & Event::MOUSE_MOTION_EVENT) {
                        MouseMotionEvent *mmev = static_cast <MouseMotionEvent *> (e);

                        /*
                         * Sprawdzamy czy onMouseOut. Uwaga! pointerInside jest unordered (hash), czyli
                         * onMouseOut odpali się w losowej kolejności. Zastanowić się, czy to bardzo źle.
                         */
                        typedef Event::PointerInsideIndex::Iterator Iterator;
                        for (Iterator i = pointerInsideIndex->begin (); i != pointerInsideIndex->end ();) {
                                M::IModel *parent;
                                G::Point copy = p;

                                if ((parent = (*i)->getParent ())) {
                                        dynamic_cast <M::IGroup *> (parent)->groupToScreen (&copy);
                                }

                                if (!(*i)->contains (copy)) {
                                        Iterator j = i;
                                        ++j;

                                        // Zawsze będzie kontroler (bo to on dodaje model do kolekcji pointerInside), ale i tak sprawdzamy.
                                        C::IController *ctr;
                                        if ((ctr = (*i)->getController ())) {
                                                C::IController::HandlingType h = ctr->onMouseOut (mmev, *i, (*i)->getView ());

                                                if (h >= C::IController::HANDLED) {
                                                        eventHandled = true;
                                                }

                                                if (h == C::IController::HANDLED_BREAK) {
                                                        break;
                                                }
                                        }

                                        pointerInsideIndex->remove (*i);
                                        i = j;
                                }
                                else {
                                        ++i;
                                }
                        }
                }

#endif

                M::IModel *model = m->findContains (p);

                if (model) {
                        eventHandled |= dispatchEventBackwards (model, mev, pointerInsideIndex);
                }
        }
        else {
                typedef Event::EventIndex::Iterator Iterator;
                typedef Event::EventIndex::Pair Pair;

                Pair pair = modeliIndex.getModels (type);

                for (Iterator i = pair.first; i != pair.second; ++i) {
                        eventHandled |= dispatchEventBackwards (i->second, e, pointerInsideIndex);
                }

                if (type & Event::QUIT_EVENT /*&& !eventHandled == HANDLED_BREAK*/) {
                        shell ()->quit ();
                }
        }


        return eventHandled;
}

/****************************************************************************/

bool EventDispatcher::dispatchEventBackwards (Model::IModel *m, IEvent *e, Event::PointerInsideIndex *pointerInsideIndex)
{
        C::IController *controller = m->getController ();
        bool eventHandled = false;

        if (controller && controller->getEventMask () & e->getType ()) {
                eventHandled |= e->runCallback (m, m->getView (), controller, pointerInsideIndex);
        }

#if 0
        std::cerr << typeid (*m).name() << ", parent=" << bool (m->getParent ()) << std::endl;
#endif

        if ((m = m->getParent ())) {
                eventHandled |= dispatchEventBackwards (m, e, pointerInsideIndex);
        }

        return eventHandled;
}

/****************************************************************************/

bool EventDispatcher::pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex)
{
        SDL_Event event;
        bool ret = false;

        while (SDL_PollEvent (&event)) {
                ret |= dispatch (m, modeliIndex, pointerInsideIndex, &event);
        }

        return ret;
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

        int viewportWidth2 = config ()->viewportWidth;
        int viewportHeight2 = config ()->viewportHeight;

        G::Point p;
        mouseToDisplay (event->button.x, event->button.y, viewportWidth2, viewportHeight2, &p.x, &p.y);
        mouseMotionEvent.setPosition (p);

#if 0
        std::cerr << event->motion.xrel << ", " << event->motion.yrel << std::endl;
#endif

        // ?
        mouseMotionEvent.setMovement (G::makePoint (event->motion.xrel, event->motion.yrel));

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

        int viewportWidth2 = config ()->viewportWidth;
        int viewportHeight2 = config ()->viewportHeight;

        G::Point p;
        mouseToDisplay (event->button.x, event->button.y, viewportWidth2, viewportHeight2, &p.x, &p.y);
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

