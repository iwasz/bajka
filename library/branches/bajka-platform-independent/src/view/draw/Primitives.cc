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

#include "view/openGl/OpenGl.h"
#include "Primitives.h"
#include "geometry/LineString.h"
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include "view/openGl/GLContext.h"
#include "model/IModel.h"
#include "model/VertexBuffer.h"

namespace View {
namespace G = Geometry;
using namespace boost::geometry;

static const GLfloat circleVAR[] = {
         0.0000f,  1.0000f, 0.0f, 1.0f,
         0.2588f,  0.9659f, 0.0f, 1.0f,
         0.5000f,  0.8660f, 0.0f, 1.0f,
         0.7071f,  0.7071f, 0.0f, 1.0f,
         0.8660f,  0.5000f, 0.0f, 1.0f,
         0.9659f,  0.2588f, 0.0f, 1.0f,
         1.0000f,  0.0000f, 0.0f, 1.0f,
         0.9659f, -0.2588f, 0.0f, 1.0f,
         0.8660f, -0.5000f, 0.0f, 1.0f,
         0.7071f, -0.7071f, 0.0f, 1.0f,
         0.5000f, -0.8660f, 0.0f, 1.0f,
         0.2588f, -0.9659f, 0.0f, 1.0f,
         0.0000f, -1.0000f, 0.0f, 1.0f,
        -0.2588f, -0.9659f, 0.0f, 1.0f,
        -0.5000f, -0.8660f, 0.0f, 1.0f,
        -0.7071f, -0.7071f, 0.0f, 1.0f,
        -0.8660f, -0.5000f, 0.0f, 1.0f,
        -0.9659f, -0.2588f, 0.0f, 1.0f,
        -1.0000f, -0.0000f, 0.0f, 1.0f,
        -0.9659f,  0.2588f, 0.0f, 1.0f,
        -0.8660f,  0.5000f, 0.0f, 1.0f,
        -0.7071f,  0.7071f, 0.0f, 1.0f,
        -0.5000f,  0.8660f, 0.0f, 1.0f,
        -0.2588f,  0.9659f, 0.0f, 1.0f,
         0.0000f,  1.0000f, 0.0f, 1.0f,
         0.0f,     0.0f,    0.0f, 1.0f  // For an extra line to see the rotation.
};

static const int circleVAR_indices = sizeof (circleVAR) / (sizeof (GLfloat) * 4);

void DrawUtil::drawCircle (View::GLContext *ctx, G::Point const &center, double angle, double radius, Color const &fg, Color const &bg, float thickness)
{
        glLineWidth (thickness);

        GLuint buffer;
        glGenBuffers (1, &buffer);
        glBindBuffer (GL_ARRAY_BUFFER, buffer);
        glBufferData (GL_ARRAY_BUFFER, sizeof (circleVAR), circleVAR, GL_STATIC_DRAW);

        glEnableVertexAttribArray (ctx->positionAttribLocation);

        glVertexAttribPointer (ctx->positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

        if (bg.a > 0) {
                glUniform4f (ctx->colorUniformLocation, bg.r, bg.g, bg.b, bg.a);
                glDrawArrays (GL_TRIANGLE_FAN, 0, circleVAR_indices);
        }

        if (fg.a > 0) {
                glUniform4f (ctx->colorUniformLocation, fg.r, fg.g, fg.b, fg.a);
                glDrawArrays (GL_LINE_STRIP, 0, circleVAR_indices);
        }
}

/****************************************************************************/

void DrawUtil::drawRectangle (View::GLContext *ctx, G::Box const &b, Color const &lineColor, Color const &fillColor, float thickness)
{
        drawRectangle (ctx, b.ll, b.ur, lineColor, fillColor, thickness);
}

/****************************************************************************/

void DrawUtil::drawRectangle (View::GLContext *ctx, G::Point const &a, G::Point const &b, Color const &fg, Color const &bg, float thickness)
{
        GLfloat verts[] = {
                a.x, a.y, 0.0, 1.0,
                a.x, b.y, 0.0, 1.0,
                b.x, b.y, 0.0, 1.0,
                b.x, a.y, 0.0, 1.0
        };

        glLineWidth (thickness);

        // Stworzenie bufora i zainicjowanie go danymi z vertex array.
        GLuint buffer;
        glGenBuffers (1, &buffer); // TODO czy tego nie trzeba skasowac jakoś?
        glBindBuffer (GL_ARRAY_BUFFER, buffer);
        glBufferData (GL_ARRAY_BUFFER, 16 * sizeof (GLfloat), verts, GL_STATIC_DRAW);

        glEnableVertexAttribArray (ctx->positionAttribLocation);

        // Użyj aktualnie zbindowanego bufora
        glVertexAttribPointer (ctx->positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

        if (bg.a > 0) {
                glUniform4f (ctx->colorUniformLocation, bg.r, bg.g, bg.b, bg.a);
                // TODO Traingle fan zrobi 4 trójkąty. A kwadrat można narysować za pomocą 2.
                glDrawArrays (GL_TRIANGLE_FAN, 0, 4);
        }

        if (fg.a > 0) {
                glUniform4f (ctx->colorUniformLocation, fg.r, fg.g, fg.b, fg.a);
                glDrawArrays (GL_LINE_LOOP, 0, 4);
        }
}

/****************************************************************************/

//void DrawUtil::drawLine (View::GLContext *ctx, G::Point const &a, G::Point const &b, Color const &color, float thickness)
//{
//        if (color.getA () > 0) {
//                GLfloat verts[] = {
//                        a.x, a.y,
//                        b.x, b.y
//                };
//
//                glVertexPointer(2, GL_FLOAT, 0, verts);
//                glDisableClientState(GL_NORMAL_ARRAY);
//                glDisableClientState(GL_COLOR_ARRAY);
//                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//                glColor4f (color.getR (), color.getG (), color.getB (), color.getA ());
//                glLineWidth(thickness);
//                glDrawArrays (GL_LINES, 0, 2);
//        }
//}

/****************************************************************************/

void DrawUtil::drawThinSegments (View::GLContext *ctx, Model::VertexBuffer const &buffer, Color const &line, Color const &fill)
{
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer (2, GL_FLOAT, buffer.stride, buffer.buffer);

        if (fill.a > 0) {
                glColor4f (fill.r, fill.g, fill.b, fill.a);
                glDrawArrays (GL_TRIANGLE_FAN, 0, buffer.numVertices);
        }

        if (line.a > 0) {
                glColor4f (line.r, line.g, line.b, line.a);
                glDrawArrays (GL_LINE_STRIP, 0, buffer.numVertices);
        }

        if (buffer.extraSegment) {
                glVertexPointer (2, GL_FLOAT, 0, buffer.extraSegment);
                glDrawArrays (GL_LINE_STRIP, 0, 2);
        }
}

/****************************************************************************/

void DrawUtil::drawThickSegments (View::GLContext *ctx, Model::VertexBuffer const &buffer, Color const &line, Color const &fill, float thickness)
{
        glVertexPointer (2, GL_FLOAT, buffer.stride, buffer.buffer);

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        if (fill.a > 0) {
                glColor4f (fill.r, fill.g, fill.b, fill.a);
                glDrawArrays (GL_TRIANGLE_FAN, 0, buffer.numVertices);
        }

//        if (line.a > 0) {
//                float *floatBuf = static_cast <float *> (buffer);
//                G::Point a;
//
//                for (size_t i = 0; i < pointCnt * 2; i += 2) {
//                        float x = *(floatBuf + i);
//                        float y = *(floatBuf + i + 1);
//                        G::Point b = Geometry::makePoint (x, y);
//
//                        if (i) {
//                                drawThickSegment (a, b, line, line, thickness);
//                        }
//
//                        a = b;
//                }
//        }
}

/****************************************************************************/

void DrawUtil::drawSegmentsPrettyJoin (View::GLContext *ctx, Model::VertexBuffer const &buffer, Color const &lineColor, Color const &fillColor, float thickness)
{
        if (thickness) {
                drawThickSegments (ctx, buffer, lineColor, fillColor, thickness);
        }
        else {
                drawThinSegments (ctx, buffer, lineColor, fillColor);
        }
}

/****************************************************************************/

void DrawUtil::drawSegments (View::GLContext *ctx, Model::VertexBuffer const &buffer, Color const &lineColor, Color const &fillColor, float thickness)
{
        glLineWidth (thickness);
        drawThinSegments (ctx, buffer, lineColor, fillColor);
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

void DrawUtil::drawThickSegment (View::GLContext *ctx, G::Point const &a, G::Point const &b, Color const &line, Color const &fill, float thickness)
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

/****************************************************************************/

//int DrawUtil::convertType (Model::VertexBuffer::PointType type)
//{
//        switch (type) {
//                case Model::VertexBuffer::FLOAT:
//                        return GL_FLOAT;
//#ifndef USE_OPENGLES
//                case Model::VertexBuffer::DOUBLE:
//                        return GL_DOUBLE;
//
//                case Model::VertexBuffer::INT:
//                        return GL_INT;
//#else
//                case Model::VertexBuffer::FIXED:
//                        return GL_FIXED;
//
//                case Model::VertexBuffer::BYTE:
//                        return GL_BYTE;
//#endif
//                case Model::VertexBuffer::SHORT:
//                        return GL_SHORT;
//                default:
//                        return GL_FLOAT;
//        }
//}

/****************************************************************************/

void DrawUtil::drawPoints (View::GLContext *ctx, Model::VertexBuffer const &buffer, Color const &color, float size)
{
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer (2, GL_FLOAT, buffer.stride, buffer.buffer);
        glPointSize (size);

        if (color.a > 0) {
                glColor4f (color.r, color.g, color.b, color.a);
                glDrawArrays (GL_POINTS, 0, buffer.numVertices);
        }
}

/****************************************************************************/

void DrawUtil::drawAABB (View::GLContext *ctx, Model::IModel *model)
{
        if (model) {
                Geometry::Box aabb = model->getBoundingBox();

#if 0
                std::cerr << typeid (*model).name () << " : aabb=" << aabb << std::endl;
#endif

                if (aabb.getWidth () && aabb.getHeight ()) {
                        DrawUtil::drawRectangle (ctx, aabb, View::Color::RED, View::Color::TRANSPARENT);
                }
        }
}

} /* namespace View */
