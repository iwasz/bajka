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
#include "GraphicsService.h"
#include <events/PointerInsideIndex.h>
#include <events/EventIdex.h>
#include <events/types/IEvent.h>
#include <model/IGroup.h>
#include <Platform.h>
#include <util/Config.h>
#include <util/Math.h>
#include <view/openGl/GLContext.h>
#include <SDL.h>

namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace G = Geometry;
using namespace Event;

/****************************************************************************/

bool EventDispatcher::process (void *systemEvent,
                               Model::IModel *model,
                               Event::EventIndex const &modeliIndex,
                               Event::PointerInsideIndex *pointerInsideIndex,
                               View::GLContext const *ctx)
{
        SDL_Event *event = static_cast <SDL_Event *> (systemEvent);
        bool ret = false;
        Event::IEvent *e = translate (event, ctx);
        ret |= dispatch (model, modeliIndex, pointerInsideIndex, e);
        return ret;
}

/****************************************************************************/

void EventDispatcher::reset ()
{
//        // Discard all pending events
//        SDL_Event event;
//
//        while (SDL_PollEvent (&event) > 0)
//                ;
}

/****************************************************************************/

void EventDispatcher::init (void *userData)
{

}

/****************************************************************************/

Event::IEvent *EventDispatcher::translate (SDL_Event *event, View::GLContext const *ctx)
{
        switch (event->type) {
        case SDL_MOUSEMOTION:
                return updateMotionEvent (event, ctx);

        case SDL_MOUSEBUTTONDOWN:
                return updateMouseButtonEvent (&motionDownEvent, event, ctx);

        case SDL_MOUSEBUTTONUP:
                return updateMouseButtonEvent (&motionUpEvent, event, ctx);

        case SDL_KEYDOWN:
                return updateKeyboardDownEvent (event);

        case SDL_KEYUP:
                return updateKeyboardUpEvent (event);

        case SDL_QUIT:
                return &quitEvent;

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

MotionEvent *EventDispatcher::updateMotionEvent (SDL_Event *event, View::GLContext const *ctx)
{
        motionMoveEvent.setSource (MOUSE);
        motionMoveEvent.setButtons (event->motion.state);
//        int pcnt = std::max (Util::numberOfSetBits (event->motion.state), 1);
//        motionMoveEvent.setPointerCount (pcnt);
        motionMoveEvent.setPointerCount (1);

//        // output->setMetaState (); TODO
//        for (int i = 0; i < pcnt; ++i) {

                MotionPointer &pointer = motionMoveEvent.getPointer (0);
                G::Point &p = pointer.position;
                ctx->mouseToDisplay (event->motion.x, event->motion.y, &p.x, &p.y);

                pointer.id = 0;
                pointer.movement.x = event->motion.xrel;
                pointer.movement.y = event->motion.yrel;
//        }

        return &motionMoveEvent;
}

/****************************************************************************/

MotionEvent *EventDispatcher::updateMouseButtonEvent (Event::MotionEvent *output, SDL_Event *event, View::GLContext const *ctx)
{
        output->setSource (MOUSE);
        output->setPointerCount (1);

        // output->setMetaState (); TODO
        unsigned int pointerIndex = event->button.button - 1;
        output->setButtons (1 << pointerIndex);

        MotionPointer &pointer = output->getPointer (pointerIndex);
        G::Point &p = pointer.position;
        ctx->mouseToDisplay (event->button.x, event->button.y, &p.x, &p.y);

        pointer.id = pointerIndex;
        pointer.movement.x = 0;
        pointer.movement.y = 0;
        return output;
}


