/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <DebugButtonController.h>
#include <events/types/Types.h>
#include <view/Primitive.h>
#include <Platform.h>
#include <util/IShell.h>

using namespace Controller;

IController::HandlingType DebugButtonController::onButtonPress (Event::ButtonPressEvent *e, Model::IModel *m, View::IView *v)
{
        View::Primitive *primitive = dynamic_cast <View::Primitive *> (v);

        if (primitive) {
                primitive->setForeground (clicked);
        }

#ifndef ANDROID
        if (sound) {
                sound->play ();
        }
#endif

        if (quit) {
                shell ()->quit ();
        }

        if (modelManager && !file.empty () && !name.empty ()) {
                modelManager->load (file, name);
        }

        return HANDLED;
}

/****************************************************************************/

IController::HandlingType DebugButtonController::onButtonRelease (Event::ButtonReleaseEvent *e, Model::IModel *m, View::IView *v)
{
        View::Primitive *primitive = dynamic_cast <View::Primitive *> (v);
        if (primitive) {
                primitive->setForeground (normal);
        }
        return HANDLED;
}

/****************************************************************************/

IController::HandlingType DebugButtonController::onMouseOver (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        View::Primitive *primitive = dynamic_cast <View::Primitive *> (v);
        if (primitive) {
                primitive->setForeground (hover);
        }
        return HANDLED;
}

/****************************************************************************/

IController::HandlingType DebugButtonController::onMouseOut (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v)
{
        View::Primitive *primitive = dynamic_cast <View::Primitive *> (v);
        if (primitive) {
                primitive->setForeground (normal);
        }
        return HANDLED;
}
