/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 26, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Foreach.h>
#include <SDL_opengl.h>

#include "GLUtil.h"

namespace OpenGL {

Model::PointList GLUtil::pointCircle;

void GLUtil::init ()
{
        double t = 0.0;
        double r = 5.0;
        int segments = 8;

        for (int i = 0; i < segments + 1; i++, t += M_PI / (segments / 2.0)) {
                pointCircle.push_back (Model::Point (r * cos (t), r * sin (t)));
        }
}

/****************************************************************************/

void GLUtil::drawPoint (const Model::Point &center, const Model::Color &color)
{
        glBegin (GL_TRIANGLE_FAN);
                glColor4d (color.getR (), color.getG (), color.getB (), color.getA ());
                glVertex2d (center.getX (), center.getY ());

                foreach (Model::Point p, pointCircle) {
                        glVertex2d (center.getX () + p.getX (), center.getY () + p.getY ());
                }
        glEnd ();
}

}
