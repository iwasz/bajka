/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include "MouseMotionEvent.h"
#include "IEvent.h"
#include "KeyboardEvent.h"
#include "MouseButtonEvent.h"
#include "QuitEvent.h"
#include "IDispatcher.h"
#include "BajkaApp.h"
#include <Reflection.h>
#include <SDL.h>

namespace Sdl {

/**
 * Generuje eventy używając do tego SDL.
 * \ingroup Events
 */
class EventDispatcher : public Event::IDispatcher {
public:
        __c (void)

        EventDispatcher () : /*observer (NULL),*/ resX2 (0), resY2 (0) {}
        virtual ~EventDispatcher () {}

        _m (init) void init ();

        void run (Model::IModel *m);

/*------getters-setters-----------------------------------------------------*/

        Ptr <Util::BajkaConfig> getConfig () const { return config; }
        _m (setConfig) void setConfig (Ptr <Util::BajkaConfig> b) { config = b; }

private:

        void translate (SDL_Event *event);

        Event::KeyboardEvent *updateKeyboardEvent (SDL_Event *event);
        Event::MouseMotionEvent *updateMouseMotionEvent (SDL_Event *event);
        Event::MouseButtonEvent *updateMouseButtonEvent (SDL_Event *event);
        Event::MouseButtonEvent *updateMouseButtonEventImpl (Event::MouseButtonEvent *output, SDL_Event *event);
        Event::MouseButton translateMouseButton (SDL_Event *event);

private:

        // This makes sense only when app is single-threaded.
        Event::MouseMotionEvent mouseMotionEvent;
        Event::KeyUpEvent keyUpEvent;
        Event::KeyDownEvent keyDownEvent;
        Event::ButtonPressEvent buttonPressEvent;
        Event::ButtonReleaseEvent buttonReleaseEvent;
        Event::QuitEvent quitEvent;

        Ptr <Util::BajkaConfig> config;

        // Screen resolution / 2
        int resX2, resY2;

        _e (EventDispatcher)
};

}

#	endif /* EVENTDISPATCHER_H_ */
