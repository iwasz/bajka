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
#include "util/IShell.h"

namespace View {
using namespace Geometry;

/****************************************************************************/

Rectangle::Rectangle ()
{
//        glGenBuffers (1, &buffer);
//        glBindBuffer (GL_ARRAY_BUFFER, buffer);
}

/****************************************************************************/

Rectangle::~Rectangle ()
{
//        glDeleteBuffers (1, &buffer);
}

/****************************************************************************/

void Rectangle::update (Model::IModel *model, Event::UpdateEvent *, Util::IShell *shell)
{
//        GLContext *ctx = shell->getGLContext ();
//        Model::IBox *cB = dynamic_cast <Model::IBox *>  (model);
//        Geometry::Box const &b = cB->getBox ();
//
//        GLfloat verts[] = {
//                b.ll.x, b.ll.y, 0.0, 1.0,
//                b.ll.x, b.ur.y, 0.0, 1.0,
//                b.ur.x, b.ur.y, 0.0, 1.0,
//                b.ur.x, b.ll.y, 0.0, 1.0
//        };
//
//        glLineWidth (getThickness ());
//        glBufferData (GL_ARRAY_BUFFER, 16 * sizeof (GLfloat), verts, GL_DYNAMIC_DRAW);
//
//        glEnableVertexAttribArray (ctx->positionAttribLocation);
//
//        // Użyj aktualnie zbindowanego bufora
//        glVertexAttribPointer (ctx->positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
//
//        Color const &bg = getBackground ();
//        if (bg.a > 0) {
//                glUniform4f (ctx->colorUniformLocation, bg.r, bg.g, bg.b, bg.a);
//                // TODO Traingle fan zrobi 4 trójkąty. A kwadrat można narysować za pomocą 2.
//                glDrawArrays (GL_TRIANGLE_FAN, 0, 4);
//        }
//
//        Color const &fg = getForeground ();
//        if (fg.a > 0) {
//                glUniform4f (ctx->colorUniformLocation, fg.r, fg.g, fg.b, fg.a);
//                glDrawArrays (GL_LINE_LOOP, 0, 4);
//        }

        Model::IBox *cB = dynamic_cast <Model::IBox *>  (model);
        assertThrow (cB, "Rectangle::update : !cB")
        Geometry::Box const &b = cB->getBox ();

        DrawUtil::drawRectangle (shell->getGLContext (),
                                 b.ll,
                                 b.ur,
                                 getForeground (),
                                 getBackground (),
                                 getThickness ());
}

} /* namespace View */
