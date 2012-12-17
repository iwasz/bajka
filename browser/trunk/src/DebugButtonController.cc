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

using namespace Controller;

Event::Handling DebugButtonController::onButtonPress (Event::MotionDownEvent *e, Model::IModel *m, View::IView *v)
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
                ::quit ();
        }

        if (modelManager && !file.empty () && !name.empty ()) {
                modelManager->load (file, name);
        }

        return Event::BREAK;
}

/****************************************************************************/

Event::Handling DebugButtonController::onButtonRelease (Event::MotionUpEvent *e, Model::IModel *m, View::IView *v)
{
        View::Primitive *primitive = dynamic_cast <View::Primitive *> (v);
        if (primitive) {
                primitive->setForeground (normal);
        }
        return Event::BREAK;
}

/****************************************************************************/

Event::Handling DebugButtonController::onMouseOver (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v)
{
        View::Primitive *primitive = dynamic_cast <View::Primitive *> (v);
        if (primitive) {
                primitive->setForeground (hover);
        }
        return Event::BREAK;
}

/****************************************************************************/

Event::Handling DebugButtonController::onMouseOut (Event::MotionMoveEvent *e, Model::IModel *m, View::IView *v)
{
        View::Primitive *primitive = dynamic_cast <View::Primitive *> (v);
        if (primitive) {
                primitive->setForeground (normal);
        }
        return Event::BREAK;
}
