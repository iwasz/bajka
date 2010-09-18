/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <Reflection.h>
#include <SDL.h>

#include "IEvent.h"
#include "KeyboardEvent.h"
#include "MouseMotionEvent.h"
#include "MouseButtonEvent.h"
#include "QuitEvent.h"
#include "IObserver.h"
#include "IDispatcher.h"
#include "BajkaApp.h"

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

        void run ();
        void translate (SDL_Event *event);

/*------getters-setters-----------------------------------------------------*/

//        Event::IObserver *getObserver () const { return observer; }
//        _m (setObserver) void setObserver (Event::IObserver *o) { observer = o; }

        Event::ObserverVector const &getObservers () const { return observers; }
        _m (setObservers) void setObservers (Event::ObserverVector const &o) { observers = o; }

        Ptr <Util::BajkaConfig> getConfig () const { return config; }
        _m (setConfig) void setConfig (Ptr <Util::BajkaConfig> b) { config = b; }

private:

        Event::KeyboardEvent *updateKeyboardEvent (SDL_Event *event);
        Event::MouseMotionEvent *updateMouseMotionEvent (SDL_Event *event);
        Event::MouseButtonEvent *updateMouseButtonEvent (SDL_Event *event);

private:

        // This makes sense only when app is single-threaded.
        Event::MouseMotionEvent mouseMotionEvent;
        Event::KeyUpEvent keyUpEvent;
        Event::KeyDownEvent keyDownEvent;
        Event::ButtonPressEvent buttonPressEvent;
        Event::ButtonReleaseEvent buttonReleaseEvent;
        Event::QuitEvent quitEvent;

//        Event::IObserver *observer;
        Event::ObserverVector observers;
        Ptr <Util::BajkaConfig> config;

        // Screen resolution / 2
        int resX2, resY2;

        _e (EventDispatcher)
};

}

#	endif /* EVENTDISPATCHER_H_ */
