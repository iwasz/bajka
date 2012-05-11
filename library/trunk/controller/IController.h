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

        /**
         * Informacja w jaki sposób metody kontrolerów obsłużyły event.
         */
        enum HandlingType {
                IGNORED, /** < Metoda ignoruje ten event */
                HANDLED, /** < Metoda obsłużyła ten event, ale pozwala przekazać go dalej do innych kontrolerów */
                HANDLED_BREAK /** Metoda obsłużyła ten event i żaden inny kontroler ma już nie dostać tego eventu. */
        };

        virtual HandlingType onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v) = 0;
                HandlingType onMouseMotionDispatch (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v, Event::PointerInsideIndex *d);
        virtual HandlingType onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onKeyDown (Event::KeyDownEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onKeyUp (Event::KeyUpEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onTimer (Event::TimerEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onQuit (Event::QuitEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onActive (Event::ActiveEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onExpose (Event::ExposeEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onResize (Event::ResizeEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) = 0;
        virtual HandlingType onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v) = 0;

/*--------------------------------------------------------------------------*/

        // Mały hack psujący interfejs - nie ma sensu wirtualne!
        unsigned int eventMask;
        unsigned int getEventMask () const { return eventMask; }
        void setEventMask (unsigned int b) { eventMask = b; }

};

} /* namespace Controller */

#	endif /* ICONTROLLER_H_ */
