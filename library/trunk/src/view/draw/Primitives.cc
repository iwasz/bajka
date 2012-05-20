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
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>

namespace View {
namespace G = Geometry;
using namespace boost::geometry;

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

void DrawUtil::drawCircle (G::Point const &center, double angle, double radius, Color const &lineColor, Color const &fillColor)
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

void DrawUtil::drawRectangle (G::Box const &b, Color const &lineColor, Color const &fillColor)
{
        drawRectangle (b.ll, b.ur, lineColor, fillColor);
}

/****************************************************************************/

void DrawUtil::drawRectangle (G::Point const &a, G::Point const &b, Color const &lineColor, Color const &fillColor)
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

void DrawUtil::drawLine (G::Point const &a, G::Point const &b, Color const &color)
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

void DrawUtil::drawThinSegments (void *buffer, size_t pointCnt, size_t stride, Color const &line, Color const &fill)
{
        glVertexPointer (2, GL_FLOAT, stride, buffer);

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        if (fill.a > 0) {
                glColor4f (fill.r, fill.g, fill.b, fill.a);
                glDrawArrays (GL_TRIANGLE_FAN, 0, pointCnt);
        }

        if (line.a > 0) {
                glColor4f (line.r, line.g, line.b, line.a);
                glDrawArrays (GL_LINE_LOOP, 0, pointCnt);
        }
}

/****************************************************************************/

void DrawUtil::drawThickSegments (void *buffer, size_t pointCnt, Color const &line, Color const &fill, float thickness)
{
        glVertexPointer (2, GL_FLOAT, 0, buffer);

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        if (fill.a > 0) {
                glColor4f (fill.r, fill.g, fill.b, fill.a);
                glDrawArrays (GL_TRIANGLE_FAN, 0, pointCnt);
        }

        if (line.a > 0) {
                float *floatBuf = static_cast <float *> (buffer);
                G::Point a;

                for (size_t i = 0; i < pointCnt * 2; i += 2) {
                        float x = *(floatBuf + i);
                        float y = *(floatBuf + i + 1);
                        G::Point b = Geometry::makePoint (x, y);

                        if (i) {
                                drawThickSegment (a, b, line, line, thickness);
                        }

                        a = b;
                }
        }
}

/****************************************************************************/

void DrawUtil::drawSegmentsPrettyJoin (void *buffer, size_t pointCnt, size_t stride, Color const &lineColor, Color const &fillColor, float thickness)
{
        if (thickness) {
                drawThickSegments (buffer, pointCnt, lineColor, fillColor, thickness);
        }
        else {
                drawThinSegments (buffer, pointCnt, stride, lineColor, fillColor);
        }
}

/****************************************************************************/

void DrawUtil::drawSegments (void *buffer, size_t pointCnt, size_t stride, Color const &lineColor, Color const &fillColor, float thickness)
{
        glLineWidth (thickness);
        drawThinSegments (buffer, pointCnt, stride, lineColor, fillColor);
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

void DrawUtil::drawThickSegment (G::Point const &a, G::Point const &b, Color const &line, Color const &fill, float thickness)
{
        glVertexPointer(3, GL_FLOAT, 0, pillVAR);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glPushMatrix(); {

                G::Point d = b;
                subtract_point (d, a);

                G::Point r = d;
                multiply_value (r, thickness / distance (G::ZERO_POINT, d));

                const GLfloat matrix[] = {
                         r.x, r.y, 0.0f, 0.0f,
                        -r.y, r.x, 0.0f, 0.0f,
                         d.x, d.y, 0.0f, 0.0f,
                         a.x, a.y, 0.0f, 1.0f,
                };
                glMultMatrixf(matrix);

                if (fill.a > 0) {
                        glColor4f (fill.r, fill.g, fill.b, fill.a);
                        glDrawArrays(GL_TRIANGLE_FAN, 0, pillVAR_count);
                }

                if (line.a > 0) {
                        glColor4f (line.r, line.g, line.b, line.a);
                        glDrawArrays(GL_LINE_LOOP, 0, pillVAR_count);
                }
        } glPopMatrix();
}

} /* namespace View */
