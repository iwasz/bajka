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

void Rectangle::update (Model::IModel *model, Event::UpdateEvent *, Util::IShell *shell)
{
        Model::IBox *cB = dynamic_cast <Model::IBox *>  (model);
        assertThrow (cB, "Rectangle::update : !cB")
        Geometry::Box const &b = cB->getBox ();

#if 0
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

        glLineWidth (getThickness ());

        // Stworzenie bufora i zainicjowanie go danymi z vertex array.
        GLuint buffer;
        glGenBuffers (1, &buffer);
        glBindBuffer (GL_ARRAY_BUFFER, buffer);
        glBufferData (GL_ARRAY_BUFFER, 16 * sizeof (GLfloat), verts, GL_STATIC_DRAW);

        // Określ indeksy uniformów i ustaw je
        GLuint currentProgramObject = shell->getGLContext ()->getCurrentProgramObject ();
        GLint colorUniformLocation = glGetUniformLocation (currentProgramObject, "color");

        // Określ indeksy atrybutów i użyj ich.
        GLint positionAttribLocation = glGetAttribLocation (currentProgramObject, "position");
        glEnableVertexAttribArray (positionAttribLocation);

        // Użyj aktualnie zbindowanego bufora
        glVertexAttribPointer (positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

        Color const &bg = getBackground ();

        if (bg.a > 0) {
                glUniform4f (colorUniformLocation, bg.r, bg.g, bg.b, bg.a);
                // TODO Traingle fan zrobi 4 trójkąty. A kwadrat można narysować za pomocą 2.
                glDrawArrays (GL_TRIANGLE_FAN, 0, 4);
        }

        Color const &fg = getForeground ();

        if (fg.a > 0) {
                glUniform4f (colorUniformLocation, fg.r, fg.g, fg.b, fg.a);
                glDrawArrays (GL_LINE_LOOP, 0, 4);
        }
}

} /* namespace View */
