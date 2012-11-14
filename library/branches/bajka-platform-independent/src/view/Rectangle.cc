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

void Rectangle::update (Model::IModel *model, Event::UpdateEvent *, Util::IShell *)
{
#if 0
        Model::IBox *cB = dynamic_cast <Model::IBox *>  (model);
        assertThrow (cB, "Rectangle::update : !cB")
        Geometry::Box const &b = cB->getBox ();
        DrawUtil::drawRectangle (b.ll,
                                 b.ur,
                                 getForeground (),
                                 getBackground (),
                                 getThickness ());
#endif

        GLfloat vVertices[] = { 0.0f, 50.0f, 0.0f, 1.0,
                                -50.0f, -50.0f, 0.0f, 1.0,
                                50.0f, -50.0f, 0.0f, 1.0 };

        // Clear the color buffer
        glClear (GL_COLOR_BUFFER_BIT);

        // Load the vertex data
        glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, vVertices);
        glEnableVertexAttribArray (0);

        glDrawArrays (GL_TRIANGLES, 0, 4);
}

} /* namespace View */
