/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TEST_CONTROLLER_H_
#define TEST_CONTROLLER_H_

#include <util/ReflectionMacros.h>
#include <controller/EmptyController.h>
#include "TestView.h"
#include <geometry/LineString.h>

/**
 * Kontroler do robienia róznych dziwnych rzeczy.
 */
struct TestController : public Controller::EmptyController {

        C__ (void)
        b_ ("EmptyController")

        TestController () : firstTime (true) {}
        virtual ~TestController () {}

        void onPreUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v);

        bool firstTime;
        TestView *p_ (testView);
        Geometry::LineString voronoi;
        Geometry::LineString delaunay;
        Geometry::LineString delaunay2;
        Geometry::LineString crossing;

        E_ (TestController)
};

#       endif /* EMPTYCONTROLLER_H_ */
