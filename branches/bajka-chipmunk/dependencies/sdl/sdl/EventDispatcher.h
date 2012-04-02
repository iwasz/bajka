/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <SDL.h>
#include "ReflectionMacros.h"
#include "IDispatcher.h"
#include "BajkaApp.h"
#include "types/Types.h"

namespace Sdl {

/**
 * Generuje eventy używając do tego SDL.
 * \ingroup Events
 */
class EventDispatcher : public Event::IDispatcher {
public:
        C__ (void)

        EventDispatcher () : app (NULL) {}
        virtual ~EventDispatcher () {}

        void run (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex);
        void reset ();

/*------getters-setters-----------------------------------------------------*/

        Util::BajkaApp *getApp () { return app; }
        void setApp (Util::BajkaApp *a) { app = a; }

private:

        Event::IEvent *translate (SDL_Event *event);
        void dispatchEventBackwards (Model::IModel *m, Event::IEvent *e, Event::PointerInsideIndex *pointerInsideIndex);

        Event::KeyboardEvent *updateKeyboardUpEvent (SDL_Event *event);
        Event::KeyboardEvent *updateKeyboardDownEvent (SDL_Event *event);
        Event::MouseMotionEvent *updateMouseMotionEvent (SDL_Event *event);
        Event::MouseButtonEvent *updateMouseButtonEvent (SDL_Event *event);
        Event::MouseButtonEvent *updateMouseButtonEventImpl (Event::MouseButtonEvent *output, SDL_Event *event);
        Event::ActiveEvent *updateActiveEvent (SDL_Event *event);
        Event::ResizeEvent *updateResizeEvent (SDL_Event *event);

        Event::MouseButton translateMouseButton (SDL_Event *event);

private:

        // This makes sense only when app is single-threaded.
        Event::MouseMotionEvent mouseMotionEvent;
        Event::KeyUpEvent keyUpEvent;
        Event::KeyDownEvent keyDownEvent;
        Event::ButtonPressEvent buttonPressEvent;
        Event::ButtonReleaseEvent buttonReleaseEvent;
        Event::QuitEvent quitEvent;
        Event::ResizeEvent resizeEvent;
        Event::ActiveEvent activeEvent;
        Event::ExposeEvent exposeEvent;

        Ptr <Util::BajkaConfig> config;
        Util::BajkaApp *app;

        E_ (EventDispatcher)
};

}

#	endif /* EVENTDISPATCHER_H_ */
