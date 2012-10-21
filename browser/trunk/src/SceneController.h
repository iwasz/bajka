/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCENECONTROLLER_H_
#define SCENECONTROLLER_H_

#include "tween/parser/ITweenFactory.h"
#include <controller/EmptyController.h>
#include <util/ReflectionMacros.h>

namespace Tween {

class SceneController : public Controller::EmptyController {
public:
        C__ (void)
        b_ ("EmptyController")
        virtual ~SceneController () {}
        m_ (init) void init ();

        HandlingType onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v);

private:

        Tween::ITweenFactory *p_ (tweenFactory)

        E_ (SceneController)
};

} /* namespace Tween */
#endif /* SCENECONTROLLER_H_ */
