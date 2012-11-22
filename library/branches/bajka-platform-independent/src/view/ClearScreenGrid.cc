/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ClearScreenGrid.h"
#include "view/openGl/OpenGl.h"
#include "Platform.h"
#include "util/Config.h"
#include <vector>

namespace View {

ClearScreenGrid::ClearScreenGrid () : density (20), gridVertsCount (0)
{
        glGenBuffers (1, &gridBuffer);
        glGenBuffers (1, &axesBuffer);

        GLfloat w = config ()->projectionWidth;
        GLfloat h = config ()->projectionHeight;
        GLfloat w2 = w / 2;
        GLfloat h2 = h / 2;

        std::vector <GLfloat> verts;

        int numX = w / density + 0.5;
        int numY = h / density + 0.5;

        // Pionowe kreski
        for (int i = 1; i < numX; ++i) {
                GLfloat x = -w2 + i * density;
                verts.push_back (x);
                verts.push_back (h2 + 1);
                verts.push_back (0); // TODO tego możnaby się pozbyć i przekazywac do shadera vec2
                verts.push_back (1);

                verts.push_back (x);
                verts.push_back (-h2 - 1);
                verts.push_back (0);
                verts.push_back (1);
        }

        // Poziome kreski
        for (int i = 1; i < numY; ++i) {
                GLfloat y = -h2 + i * density;
                verts.push_back (w2 + 1);
                verts.push_back (y);
                verts.push_back (0);
                verts.push_back (1);

                verts.push_back (-w2 - 1);
                verts.push_back (y);
                verts.push_back (0);
                verts.push_back (1);
        }

        gridVertsCount = verts.size () / 4u;

        glBindBuffer (GL_ARRAY_BUFFER, gridBuffer);
        glBufferData (GL_ARRAY_BUFFER, verts.size () * sizeof (GLfloat), &verts.front (), GL_STATIC_DRAW);
        glEnableVertexAttribArray (glContext ()->positionAttribLocation);
        glVertexAttribPointer (glContext ()->positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

        GLfloat verts1[] = {
                -w2 - 1, 0,       0, 1,
                w2 + 1,  0,       0, 1,
                0,       -h2 - 1, 0, 1,
                0,       h2 + 1,  0, 1
        };

        glBindBuffer (GL_ARRAY_BUFFER, axesBuffer);
        glBufferData (GL_ARRAY_BUFFER, 16 * sizeof (GLfloat), verts1, GL_STATIC_DRAW);
        glEnableVertexAttribArray (glContext ()->positionAttribLocation);
        glVertexAttribPointer (glContext ()->positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer (GL_ARRAY_BUFFER, 0);
}

/****************************************************************************/

ClearScreenGrid::~ClearScreenGrid ()
{
        glDeleteBuffers (1, &gridBuffer);
        glDeleteBuffers (1, &axesBuffer);
}

/****************************************************************************/

void ClearScreenGrid::update (Model::IModel *, Event::UpdateEvent *e, View::GLContext *ctx)
{
        glClearColor (color.r, color.g, color.b, color.a);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (gridColor.getA () <= 0) {
                return;
        }

        glLineWidth (1);
        glEnableVertexAttribArray (ctx->positionAttribLocation);

        glBindBuffer (GL_ARRAY_BUFFER, gridBuffer);
        glUniform4f (ctx->colorUniformLocation, gridColor.r, gridColor.g, gridColor.b, gridColor.a);
        glDrawArrays (GL_LINES, 0, gridVertsCount);

        glBindBuffer (GL_ARRAY_BUFFER, axesBuffer);
        glUniform4f (ctx->colorUniformLocation, gridColor.r - 0.1, gridColor.g - 0.1, gridColor.b - 0.1, gridColor.a);
        glDrawArrays (GL_LINES, 0, 4);

        glBindBuffer (GL_ARRAY_BUFFER, 0);
}

} /* namespace View */
