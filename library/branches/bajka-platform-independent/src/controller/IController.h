/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ICONTROLLER_H_
#define BAJKA_ICONTROLLER_H_

#include <core/Object.h>
#include "events/Handling.h"

namespace Model {
class IModel;
}

namespace View {
class IView;
}

namespace Event {
class IEvent;
class ButtonPressEvent;
class ButtonReleaseEvent;
class MouseMotionEvent;
class KeyDownEvent;
class KeyUpEvent;
class QuitEvent;
class ResizeEvent;
class UpdateEvent;
class ManagerEvent;

class PointerInsideIndex;
}

namespace Controller {

/**
 * Oszukany interfejs :D
 */
struct IController : public Core::Object {

        IController () : eventMask (0) {}
        virtual ~IController () {}

        virtual void onPreUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual void onUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual void onPostUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v) = 0;

/*--------------------------------------------------------------------------*/

        virtual Event::Handling onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual Event::Handling onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v) = 0;
                Event::Handling onMouseMotionDispatch (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v, Event::PointerInsideIndex *d);
        virtual Event::Handling onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual Event::Handling onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual Event::Handling onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual Event::Handling onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual Event::Handling onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual Event::Handling onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual Event::Handling onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual Event::Handling onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual Event::Handling onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) = 0;

/*--------------------------------------------------------------------------*/

        // Mały hack psujący interfejs - nie ma sensu wirtualne!
        unsigned int eventMask;
        unsigned int getEventMask () const { return eventMask; }
        void setEventMask (unsigned int b) { eventMask = b; }

};

} /* namespace Controller */

#	endif /* ICONTROLLER_H_ */
