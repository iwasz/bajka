/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TEST_VIEW_POLY_H_
#define TEST_VIEW_POLY_H_

#include <view/Primitive.h>
#include "view/openGl/OpenGl.h"
#include <geometry/LineString.h>

/**
 *
 */
class TestView : public View::Primitive {
public:

        C__ (void)
        b_ ("Primitive")

        TestView ();
        virtual ~TestView ();
        virtual void update (Model::IModel *model, Event::UpdateEvent *e, View::GLContext *ctx);

        Geometry::LineString *voronoi;

private:

        GLuint buffer;

        E_ (TestView)
};

#	endif /* CIRCLE_H_ */
