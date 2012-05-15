/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 *                                                                          *
 *  Parts of this code are taken from chipmunk demo app.                    *
 *                                                                          *
 ****************************************************************************/

#include "OpenGl.h"
#include <chipmunk.h>
#include "Primitives.h"
#include "../../geometry/LineString.h"

namespace View {

namespace G = Geometry;

static const GLfloat circleVAR[] = {
         0.0000f,  1.0000f,
         0.2588f,  0.9659f,
         0.5000f,  0.8660f,
         0.7071f,  0.7071f,
         0.8660f,  0.5000f,
         0.9659f,  0.2588f,
         1.0000f,  0.0000f,
         0.9659f, -0.2588f,
         0.8660f, -0.5000f,
         0.7071f, -0.7071f,
         0.5000f, -0.8660f,
         0.2588f, -0.9659f,
         0.0000f, -1.0000f,
        -0.2588f, -0.9659f,
        -0.5000f, -0.8660f,
        -0.7071f, -0.7071f,
        -0.8660f, -0.5000f,
        -0.9659f, -0.2588f,
        -1.0000f, -0.0000f,
        -0.9659f,  0.2588f,
        -0.8660f,  0.5000f,
        -0.7071f,  0.7071f,
        -0.5000f,  0.8660f,
        -0.2588f,  0.9659f,
         0.0000f,  1.0000f,
         0.0f, 0.0f, // For an extra line to see the rotation.
};
static const int circleVAR_count = sizeof(circleVAR)/sizeof(GLfloat)/2;

void DrawUtil::drawCircle (Geometry::Point const &center, double angle, double radius, Color const &lineColor, Color const &fillColor)
{
        glVertexPointer(2, GL_FLOAT, 0, circleVAR);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glPushMatrix(); {
                glTranslatef(center.x, center.y, 0.0f);
                glRotatef(angle, 0.0f, 0.0f, 1.0f);
                glScalef(radius, radius, 1.0f);

                if (fillColor.getA () > 0){
                        glColor4f (fillColor.getR (), fillColor.getG (), fillColor.getB (), fillColor.getA ());
                        glDrawArrays(GL_TRIANGLE_FAN, 0, circleVAR_count - 1);
                }

                if (lineColor.getA () > 0){
                        glColor4f (lineColor.getR (), lineColor.getG (), lineColor.getB (), lineColor.getA ());
                        glDrawArrays(GL_LINE_STRIP, 0, circleVAR_count);
                }
        } glPopMatrix();
}

/****************************************************************************/

void DrawUtil::drawRectangle (Geometry::Box const &b, Color const &lineColor, Color const &fillColor)
{
        drawRectangle (b.ll, b.ur, lineColor, fillColor);
}

/****************************************************************************/

void DrawUtil::drawRectangle (Geometry::Point const &a, Geometry::Point const &b, Color const &lineColor, Color const &fillColor)
{
        static GLfloat verts[] = {
                a.x, a.y,
                a.x, b.y,
                b.x, b.y,
                b.x, a.y
        };

        glVertexPointer (2, GL_FLOAT, 0, verts);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        if (fillColor.getA () > 0) {
                glColor4f (fillColor.getR (), fillColor.getG (), fillColor.getB (), fillColor.getA ());
                glDrawArrays (GL_TRIANGLE_FAN, 0, 4);
        }

        if (lineColor.getA () > 0) {
                glColor4f (lineColor.getR (), lineColor.getG (), lineColor.getB (), lineColor.getA ());
                glDrawArrays (GL_LINE_LOOP, 0, 4);
        }
}

/****************************************************************************/

void DrawUtil::drawLine (Geometry::Point const &a, Geometry::Point const &b, Color const &color)
{
        if (color.getA () > 0) {
                GLfloat verts[] = {
                        a.x, a.y,
                        b.x, b.y
                };

                glVertexPointer(2, GL_FLOAT, 0, verts);
                glDisableClientState(GL_NORMAL_ARRAY);
                glDisableClientState(GL_COLOR_ARRAY);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                glColor4f (color.getR (), color.getG (), color.getB (), color.getA ());
                glDrawArrays (GL_LINES, 0, 2);
        }
}

/****************************************************************************/

void DrawUtil::draw ()
{
//        G::LineString points;
        std::vector <G::Point> points;

        points.push_back (G::makePoint (-50, 50));
        points.push_back (G::makePoint (50, 50));
        points.push_back (G::makePoint (50, -50));
        points.push_back (G::makePoint (-50, -50));

        glVertexPointer (2, GL_FLOAT, 0, &points[0]);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glColor4f (0, 0, 0, 1);
        glDrawArrays (GL_LINE_LOOP, 0, 4);
}

} /* namespace View */
