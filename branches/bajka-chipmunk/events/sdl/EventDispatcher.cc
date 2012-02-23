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

namespace Sdl {
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace G = Geometry;
using namespace Event;

/****************************************************************************/
// CO TO ROBIŁO!?!?!?

//static void runRec (Model::IModel *m, Event::IEvent *e)
//{
//        C::IController *c;
//
//        if ((c = m->getController ())) {
//                if (e && e->getType () & c->getEventMask ()) {
//                        if (!e->runCallback (m, m->getView (), m->getController ())) {
//                                return;
//                        }
//                }
//                else {
//                	return;
//                }
//        }
//
//        if (m->isGroup ()) {
//                M::IGroup *g = dynamic_cast<M::IGroup *> (m);
//                std::for_each (g->begin (), g->end (), boost::bind (runRec, _1, e));
//        }
//}

/****************************************************************************/
#define checkBreak() { if (app->getDropIteration ()) { break; } }
#define checkContinue() { if (app->getDropIteration ()) { continue; } }

void EventDispatcher::dispatchEventBackwards (Model::IModel *m, IEvent *e)
{
        C::IController *controller = m->getController ();

        if (controller && controller->getEventMask () & e->getType ()) {
                e->runCallback (m, m->getView (), controller, this);

                if (app->getDropIteration ()) {
                        return;
                }
        }

        if ((m = m->getParent ())) {
                dispatchEventBackwards (m, e);
        }
}

/****************************************************************************/

void EventDispatcher::run (Model::IModel *m, ModelIndex const &modeliIndex)
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
                        M::IModel *model = m->findContains (p);

//                        if (type & Event::MOUSE_MOTION_EVENT && model != prevMouseModel) {
//                                MouseMotionEvent *mmev = static_cast <MouseMotionEvent *> (e);
//
//                                if (prevMouseModel) {
//                                        C::IController *ctr = prevMouseModel->getController ();
//
//                                        if (ctr && ctr->getEventMask () & Event::MOUSE_OUT_EVENT) {
//                                                ctr->onMouseOut (mmev, prevMouseModel, prevMouseModel->getView ());
//                                        }
//                                }
//
//                                checkBreak ();
//
//                                if (model) {
//                                        C::IController *ctr = model->getController ();
//
//                                        if (ctr && ctr->getEventMask () & Event::MOUSE_OVER_EVENT) {
//                                                ctr->onMouseOver (mmev, model, model->getView ());
//                                        }
//                                }
//
//                                checkBreak ();
//                        }
//
//                        prevMouseModel = model;

                        if (!model) {
                                return;
                        }

                        dispatchEventBackwards (model, mev);
                        checkBreak ();
                }
                else {
                        std::pair <ModelIndex::const_iterator, ModelIndex::const_iterator> t = modeliIndex.equal_range (type);

                        for (ModelIndex::const_iterator i = t.first; i != t.second; ++i) {
                                dispatchEventBackwards (i->second, e);
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

void EventDispatcher::setPointerInside (Model::IModel *m)
{
        pointerInside.insert (m);
}

/****************************************************************************/

void EventDispatcher::removePointerInside (Model::IModel *m)
{
        pointerInside.erase (m);
}

/****************************************************************************/

bool EventDispatcher::isPointerInside (Model::IModel *m) const
{
        return pointerInside.find (m) != pointerInside.end ();
}

} // nam
