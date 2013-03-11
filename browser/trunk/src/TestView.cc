/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TestView.h"
#include <model/static/Box.h>
#include <model/VertexBuffer.h>
#include <model/IVertexBufferEnabled.h>
#include <util/Exceptions.h>
#include <view/openGl/OpenGl.h>

using Model::VertexBuffer;
using namespace Geometry;

/****************************************************************************/

TestView::TestView () : voronoi (NULL)
{
        glGenBuffers (1, &buffer);
}

/****************************************************************************/

TestView::~TestView ()
{
        glDeleteBuffers (1, &buffer);
}

/****************************************************************************/

void TestView::update (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{

        glLineWidth (getThickness ());
        glPointSize (2);
        glEnableVertexAttribArray (ctx->positionAttribLocation);

        if (delaunay) {
                glBindBuffer (GL_ARRAY_BUFFER, buffer);
                glBufferData (GL_ARRAY_BUFFER, delaunay->size () * 2 * sizeof (GLfloat), (void *)&delaunay->front (), GL_DYNAMIC_DRAW);
                glVertexAttribPointer (ctx->positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
                glBindBuffer (GL_ARRAY_BUFFER, 0);

                glUniform4f (ctx->colorUniformLocation, 0, 1, 0, 0.5);
                glDrawArrays (GL_LINES, 0, delaunay->size ());
//                glDrawArrays (GL_TRIANGLES, 0, delaunay->size ());

        }

        if (delaunay2) {
                glBindBuffer (GL_ARRAY_BUFFER, buffer);
                glBufferData (GL_ARRAY_BUFFER, delaunay2->size () * 2 * sizeof (GLfloat), (void *)&delaunay2->front (), GL_DYNAMIC_DRAW);
                glVertexAttribPointer (ctx->positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
                glBindBuffer (GL_ARRAY_BUFFER, 0);

                glUniform4f (ctx->colorUniformLocation, 0, 0, 1, 0.2);
                glDrawArrays (GL_TRIANGLES, 0, delaunay2->size ());

        }

        if (crossing) {
                glBindBuffer (GL_ARRAY_BUFFER, buffer);
                glBufferData (GL_ARRAY_BUFFER, crossing->size () * 2 * sizeof (GLfloat), (void *)&crossing->front (), GL_DYNAMIC_DRAW);
                glVertexAttribPointer (ctx->positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
                glBindBuffer (GL_ARRAY_BUFFER, 0);

                glUniform4f (ctx->colorUniformLocation, 1, 0, 0, 0.1);
//                glDrawArrays (GL_LINES, 0, delaunay->size ());
                glDrawArrays (GL_TRIANGLES, 0, crossing->size ());

        }

        if (voronoi) {
                glBindBuffer (GL_ARRAY_BUFFER, buffer);
                glBufferData (GL_ARRAY_BUFFER, voronoi->size () * 2 * sizeof (GLfloat), (void *)&voronoi->front (), GL_DYNAMIC_DRAW);
                glVertexAttribPointer (ctx->positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
                glBindBuffer (GL_ARRAY_BUFFER, 0);

                glUniform4f (ctx->colorUniformLocation, 1, 1, 1, 0.2);
                glDrawArrays (GL_LINES, 0, voronoi->size ());
        }

        // Actual object
        Model::IVertexBufferEnabled *array = dynamic_cast <Model::IVertexBufferEnabled *>  (model);
        VertexBuffer vBuf = array->getVertexBuffer ();
        glBindBuffer (GL_ARRAY_BUFFER, buffer);
        glBufferData (GL_ARRAY_BUFFER, vBuf.numVertices * 2 * sizeof (GLfloat), vBuf.buffer, GL_DYNAMIC_DRAW);
        glVertexAttribPointer (ctx->positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer (GL_ARRAY_BUFFER, 0);

//        View::Color const &bg = getBackground ();
//        if (bg.a > 0) {
//                glUniform4f (ctx->colorUniformLocation, bg.r, bg.g, bg.b, bg.a);
//                glDrawArrays (GL_TRIANGLE_FAN, 0, vBuf.numVertices);
//        }

        View::Color const &fg = getForeground ();
        if (fg.a > 0) {
                glUniform4f (ctx->colorUniformLocation, fg.r, fg.g, fg.b, fg.a);
//                glDrawArrays (GL_LINE_LOOP, 0, vBuf.numVertices);
                glDrawArrays (GL_POINTS, 0, vBuf.numVertices);

                glPointSize (4);
//                glUniform4f (ctx->colorUniformLocation, fg.r, fg.g, fg.b, fg.a);
//                glDrawArrays (GL_POINTS, 0, 3);
//                glDrawArrays (GL_POINTS, 450, 1);

                glUniform4f (ctx->colorUniformLocation, 0, 0, 1, 1);
//                glDrawArrays (GL_POINTS, 117, 1);
//                glDrawArrays (GL_POINTS, 120, 1);
//                glDrawArrays (GL_POINTS, 350, 1);
//
//                glDrawArrays (GL_POINTS, 349, 1);
//                glDrawArrays (GL_POINTS, 321, 1);
//                glDrawArrays (GL_POINTS, 350, 1);
//
//                glDrawArrays (GL_POINTS, 349, 1);
//                glDrawArrays (GL_POINTS, 451, 1);
//                glDrawArrays (GL_POINTS, 321, 1);

                glDrawArrays (GL_POINTS, 306, 1);

        }

        glDisableVertexAttribArray (ctx->positionAttribLocation);
}

