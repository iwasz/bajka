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
#include "../../dependencies/openGl/Util.h"
#include "../../../events/PointerInsideIndex.h"
#include "../../../events/EventIdex.h"

namespace Sdl {
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace G = Geometry;
using namespace Event;

/****************************************************************************/

#define checkBreak() { if (app->getDropIteration ()) { break; } }
#define checkContinue() { if (app->getDropIteration ()) { continue; } }

/****************************************************************************/

void EventDispatcher::dispatchEventBackwards (Model::IModel *m, IEvent *e, Event::PointerInsideIndex *pointerInsideIndex)
{
        C::IController *controller = m->getController ();

        if (controller && controller->getEventMask () & e->getType ()) {
                e->runCallback (m, m->getView (), controller, pointerInsideIndex);

                if (app->getDropIteration ()) {
                        return;
                }
        }

        if ((m = m->getParent ())) {
                dispatchEventBackwards (m, e, pointerInsideIndex);
        }
}

/****************************************************************************/

void EventDispatcher::run (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex)
{
        SDL_Event event;

        while (SDL_PollEvent (&event)) {
                Event::IEvent *e = translate (&event);

                if (!e) {
                        return;
                }

                Event::Type type = e->getType();

                if (type & MOUSE_EVENTS) {
                        MouseEvent *mev = static_cast <MouseEvent *> (e);
                        G::Point const &p = mev->getPosition ();

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
                                                        ctr->onMouseOut (mmev, *i, (*i)->getView ());
                                                }

                                                pointerInsideIndex->remove (*i);
                                                i = j;
                                        }
                                        else {
                                                ++i;
                                        }
                                }
                        }

                        checkBreak ();

                        M::IModel *model = m->findContains (p);

                        if (model) {
                                dispatchEventBackwards (model, mev, pointerInsideIndex);
                                checkBreak ();
                        }
                }
                else {
                        typedef Event::EventIndex::Iterator Iterator;
                        typedef Event::EventIndex::Pair Pair;

                        Pair pair = modeliIndex.getModels (type);

                        for (Iterator i = pair.first; i != pair.second; ++i) {
                                dispatchEventBackwards (i->second, e, pointerInsideIndex);
                                checkBreak ();
                        }
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
        V::Util::mouseToDisplay (event->button.x, event->button.y, resX2, resY2, &p.x, &p.y);
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
        V::Util::mouseToDisplay (event->button.x, event->button.y, resX2, resY2, &p.x, &p.y);
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
