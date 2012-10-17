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
#include <sound/Source.h>

/**
 *
 */
class DebugButtonController : public Controller::EmptyController {
public:
        C__ (void)
        b_ ("EmptyController")
        virtual ~DebugButtonController () {}

/*--------------------------------------------------------------------------*/

        virtual HandlingType onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v);
        virtual HandlingType onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v);
        virtual HandlingType onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);
        virtual HandlingType onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);

private:

        View::Color P_ (clicked);
        View::Color P_ (hover);
        View::Color P_ (normal);
        Model::IModelManager *p_ (modelManager);
        std::string p_ (file);
        std::string p_ (name);
        Source *p_ (sound);

        E_ (DebugButtonController)
};

#	endif /* DEBUGCONTROLLER_H_ */
