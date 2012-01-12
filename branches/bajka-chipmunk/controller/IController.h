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
}

namespace Controller {

/**
 *
 */
struct IController : public Core::Object {

        virtual ~IController () {}

        virtual bool preUpdate (Model::IModel *m, View::IView *v) = 0;
        virtual bool update (Model::IModel *m, View::IView *v) = 0;
        virtual bool postUpdate (Model::IModel *m, View::IView *v) = 0;

/*--------------------------------------------------------------------------*/

        virtual bool onButtonPress (Event::ButtonPressEvent *e) = 0;
        virtual bool onButtonRelease (Event::ButtonReleaseEvent *e) = 0;
        virtual bool onMouseMotion (Event::MouseMotionEvent *e) = 0;
        virtual bool onKeyDown (Event::KeyDownEvent *e) = 0;
        virtual bool onKeyUp (Event::KeyUpEvent *e) = 0;
        virtual bool onTimer (Event::TimerEvent *e) = 0;
        virtual bool onQuit (Event::QuitEvent *e) = 0;

};

} /* namespace Controller1 */

#	endif /* ICONTROLLER_H_ */
