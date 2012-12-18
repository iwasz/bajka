/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DEBUG_BUTTON_CONTROLLER_H_
#define DEBUG_BUTTON_CONTROLLER_H_

#include <util/ReflectionMacros.h>
#include <controller/EmptyController.h>
#include <view/draw/Color.h>
#include <model/manager/IModelManager.h>
#ifndef ANDROID
#include <sound/Source.h>
#endif
/**
 *
 */
class DebugButtonController : public Controller::EmptyController {
public:
        C__ (void)
        b_ ("EmptyController")
        DebugButtonController () : quit (false) {}
        virtual ~DebugButtonController () {}

/*--------------------------------------------------------------------------*/

        virtual Event::Handling onMotionDown (Event::MotionDownEvent *e, Model::IModel *m, View::IView *v);
        virtual Event::Handling onMotionUp (Event::MotionUpEvent *e, Model::IModel *m, View::IView *v);
        virtual Event::Handling onMotionOver (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v);
        virtual Event::Handling onMotionOut (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v);

private:

        View::Color P_ (clicked);
        View::Color P_ (hover);
        View::Color P_ (normal);
        Model::IModelManager *p_ (modelManager);
        std::string p_ (file);
        std::string p_ (name);
#ifndef ANDROID
        Source *p_ (sound);
#endif
        bool p_ (quit)

        E_ (DebugButtonController)
};

#	endif /* DEBUGCONTROLLER_H_ */
