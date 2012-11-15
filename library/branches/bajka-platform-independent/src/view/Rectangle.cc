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
        Model::IBox *cB = dynamic_cast <Model::IBox *>  (model);
        assertThrow (cB, "Rectangle::update : !cB")
        Geometry::Box const &b = cB->getBox ();
#if 1
        DrawUtil::drawRectangle (b.ll,
                                 b.ur,
                                 getForeground (),
                                 getBackground (),
                                 getThickness ());
#endif

        Point const &pa = b.ll;
        Point const &pb = b.ur;

        GLfloat verts[] = {
                pa.x, pa.y, 0.0, 1.0,
                pa.x, pb.y, 0.0, 1.0,
                pb.x, pb.y, 0.0, 1.0,
                pb.x, pa.y, 0.0, 1.0
        };

        // Load the vertex data
        glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, verts);
        glEnableVertexAttribArray (0);
        glDrawArrays (GL_LINE_LOOP, 0, 4);
}

} /* namespace View */
