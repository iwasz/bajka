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
#include "../src/Platform.h"

namespace Demo {
using namespace Tween;

Event::Handling Instructions1Controller::onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        printlog ("Instructions1Controller::onManagerLoad");

//        timeline ()->add (
//                to (testModel, 1000, BACK_OUT)->
//                        rel (SCALE, 4)->
//                        rel (ANGLE, 90)->
//                        rel (X, 100)->
//                        rel (Y, 100)
//        )->repeat (1, true)->
//        start ();

        multi ()->add (
                to (envelope1, 2000, QUAD_OUT)->
                        rel (Y, 50)
        )->add (
                to (envelope2, 2000, QUAD_OUT)->
                        rel (Y, 50)->
                        delay (500)
        )->add (
                to (envelope3, 2000, QUAD_OUT)->
                        rel (Y, 50)->
                        delay (1000)
        )->add (
                to (envelope4, 2000, QUAD_OUT)->
                        rel (Y, 50)->
                        delay (1500)
        )->add (
                to (envelope5, 2000, QUAD_OUT)->
                        rel (Y, 50)->
                        delay (2000)
        )->
        repeat (1, true)->
        start ();

//        to (envelope1, 1000, QUAD_OUT)->
//                rel (Y, 50)->
//                start ();

        return Controller::IController::Event::BREAK;
}

/****************************************************************************/

Event::Handling Instructions1Controller::onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        std::cerr << "Instructions1Controller::onManagerUnload" << std::endl;
        return Controller::IController::Event::BREAK;
}

} /* namespace Demo */
