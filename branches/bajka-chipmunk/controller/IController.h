/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ICONTROLLER_H_
#define BAJKA_ICONTROLLER_H_

#include <Object.h>

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
class TimerEvent;
class QuitEvent;
class ActiveEvent;
class ExposeEvent;
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

        virtual bool onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v) = 0;
                bool onMouseMotionDispatch (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v, Event::PointerInsideIndex *d);
        virtual bool onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual bool onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) = 0;

        // Mały hack psujący interfejs - nie ma sensu wirtualne!
        unsigned int eventMask;
        unsigned int getEventMask () const { return eventMask; }
        void setEventMask (unsigned int b) { eventMask = b; }

};

} /* namespace Controller */

#	endif /* ICONTROLLER_H_ */
