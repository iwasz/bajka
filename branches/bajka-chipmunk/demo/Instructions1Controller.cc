/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Instructions1Controller.h"
#include "../model/IModel.h"
#include "../tween/Tween.h"

namespace Demo {

bool Instructions1Controller::onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        timeline ()->add (
                to (testModel, 1000, BACK_OUT)->
                        rel (SCALE, 4)->
                        rel (ANGLE, 90)->
                        rel (X, 100)->
                        rel (Y, 100)
        )->repeat (1, true)->
        start ();

        return true;
}

/****************************************************************************/

bool Instructions1Controller::onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        std::cerr << "Instructions1Controller::onManagerUnload" << std::endl;
        return true;
}

} /* namespace Demo */
