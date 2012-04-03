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
        GLfloat verts[] = {
                a.x, a.y,
                a.x, b.y,
                b.x, b.y,
                b.x, a.y
        };

        glVertexPointer (4, GL_FLOAT, 0, verts);

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
                glColor4f (color.getR (), color.getG (), color.getB (), color.getA ());
                glDrawArrays (GL_LINES, 0, 2);
        }
}

/****************************************************************************/

static const GLfloat pillVAR[] = {
         0.0000f,  1.0000f, 1.0f,
         0.2588f,  0.9659f, 1.0f,
         0.5000f,  0.8660f, 1.0f,
         0.7071f,  0.7071f, 1.0f,
         0.8660f,  0.5000f, 1.0f,
         0.9659f,  0.2588f, 1.0f,
         1.0000f,  0.0000f, 1.0f,
         0.9659f, -0.2588f, 1.0f,
         0.8660f, -0.5000f, 1.0f,
         0.7071f, -0.7071f, 1.0f,
         0.5000f, -0.8660f, 1.0f,
         0.2588f, -0.9659f, 1.0f,
         0.0000f, -1.0000f, 1.0f,

         0.0000f, -1.0000f, 0.0f,
        -0.2588f, -0.9659f, 0.0f,
        -0.5000f, -0.8660f, 0.0f,
        -0.7071f, -0.7071f, 0.0f,
        -0.8660f, -0.5000f, 0.0f,
        -0.9659f, -0.2588f, 0.0f,
        -1.0000f, -0.0000f, 0.0f,
        -0.9659f,  0.2588f, 0.0f,
        -0.8660f,  0.5000f, 0.0f,
        -0.7071f,  0.7071f, 0.0f,
        -0.5000f,  0.8660f, 0.0f,
        -0.2588f,  0.9659f, 0.0f,
         0.0000f,  1.0000f, 0.0f,
};

static const int pillVAR_count = sizeof(pillVAR)/sizeof(GLfloat)/3;

void DrawUtil::drawFatLine (Geometry::Point const &a, Geometry::Point const &b, double radius, Color const &lineColor, Color const &fillColor)
{
        if (radius) {
                glVertexPointer(3, GL_FLOAT, 0, pillVAR);

                glPushMatrix(); {

                        G::Point d = b - a;
                        G::Point r = d * radius / d.distance ();

                        const GLfloat matrix[] = {
                                 r.x, r.y, 0.0f, 0.0f,
                                -r.y, r.x, 0.0f, 0.0f,
                                 d.x, d.y, 0.0f, 0.0f,
                                 a.x, a.y, 0.0f, 1.0f,
                        };
                        glMultMatrixf(matrix);

                        if (fillColor.getA () > 0){
                                glColor4f (fillColor.getR (), fillColor.getG (), fillColor.getB (), fillColor.getA ());
                                glDrawArrays(GL_TRIANGLE_FAN, 0, pillVAR_count);
                        }

                        if (lineColor.getA () > 0){
                                glColor4f (lineColor.getR (), lineColor.getG (), lineColor.getB (), lineColor.getA ());
                                glDrawArrays(GL_LINE_LOOP, 0, pillVAR_count);
                        }

                } glPopMatrix();

        } else {
                drawLine (a, b, lineColor);
        }
}

} /* namespace View */
