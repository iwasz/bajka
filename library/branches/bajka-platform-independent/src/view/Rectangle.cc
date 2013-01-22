/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Rectangle.h"
#include "draw/Primitives.h"
#include "model/static/Box.h"
#include "model/physics/CPBox.h"
#include "util/Exceptions.h"
#include "view/openGl/OpenGl.h"

namespace View {
using namespace Geometry;

/****************************************************************************/

Rectangle::Rectangle ()
{
        glGenBuffers (1, &buffer);
}

/****************************************************************************/

Rectangle::~Rectangle ()
{
        glDeleteBuffers (1, &buffer);
}

/****************************************************************************/

void Rectangle::update (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{
        Model::IBox *cB = dynamic_cast <Model::IBox *>  (model);
        Geometry::Box const &b = cB->getBox ();

        GLfloat verts[] = {
                b.ur.x, b.ll.y, 0.0, 1.0,
                b.ur.x, b.ur.y, 0.0, 1.0,
                b.ll.x, b.ur.y, 0.0, 1.0,
                b.ll.x, b.ll.y, 0.0, 1.0
        };

        glLineWidth (getThickness ());
        glBindBuffer (GL_ARRAY_BUFFER, buffer);
        glBufferData (GL_ARRAY_BUFFER, 16 * sizeof (GLfloat), verts, GL_DYNAMIC_DRAW);
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
