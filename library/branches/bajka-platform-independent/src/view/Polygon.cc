/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Polygon.h"
#include "draw/Primitives.h"
#include "model/static/Box.h"
#include "model/physics/CPBox.h"
#include "util/Exceptions.h"
#include "view/openGl/OpenGl.h"
#include "model/VertexBuffer.h"
#include "model/IVertexBufferEnabled.h"

using Model::VertexBuffer;

namespace View {
using namespace Geometry;

/****************************************************************************/

Polygon::Polygon ()
{
        glGenBuffers (1, &buffer);
}

/****************************************************************************/

Polygon::~Polygon ()
{
        glDeleteBuffers (1, &buffer);
}

/****************************************************************************/

void Polygon::update (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{
        Model::IVertexBufferEnabled *array = dynamic_cast <Model::IVertexBufferEnabled *>  (model);
        VertexBuffer vBuf = array->getVertexBuffer ();

        glLineWidth (getThickness ());
        glBindBuffer (GL_ARRAY_BUFFER, buffer);
        glBufferData (GL_ARRAY_BUFFER, vBuf.numVertices * 2 * sizeof (GLfloat), vBuf.buffer, GL_DYNAMIC_DRAW);
        glVertexAttribPointer (ctx->positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer (GL_ARRAY_BUFFER, 0);

        glEnableVertexAttribArray (ctx->positionAttribLocation);

        Color const &bg = getBackground ();
        if (bg.a > 0) {
                glUniform4f (ctx->colorUniformLocation, bg.r, bg.g, bg.b, bg.a);
                glDrawArrays (GL_TRIANGLE_FAN, 0, 4);
        }

        Color const &fg = getForeground ();
        if (fg.a > 0) {
                glUniform4f (ctx->colorUniformLocation, fg.r, fg.g, fg.b, fg.a);
                glDrawArrays (GL_LINE_LOOP, 0, 4);
        }

        glDisableVertexAttribArray (ctx->positionAttribLocation);
}

} /* namespace View */
