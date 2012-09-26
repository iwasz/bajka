/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ClearScreenGrid.h"
#include "openGl/OpenGl.h"
#include "Platform.h"
#include "util/Config.h"
#include <vector>

namespace View {

void ClearScreenGrid::update (Model::IModel *, Event::UpdateEvent *e)
{
        glClearColor (color.r, color.g, color.b, color.a);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (gridColor.getA () <= 0) {
                return;
        }

        GLfloat w = config ()->projectionWidth;
        GLfloat h = config ()->projectionHeight;
        GLfloat w2 = w / 2;
        GLfloat h2 = h / 2;

        std::vector <GLfloat> verts;

        int numX = w / density + 0.5;
        int numY = h / density + 0.5;

        for (int i = 1; i < numX; ++i) {
                GLfloat x = -w2 + i * density;
                verts.push_back (x);
                verts.push_back (h2 + 1);
                verts.push_back (x);
                verts.push_back (-h2 - 1);
        }

        for (int i = 1; i < numY; ++i) {
                GLfloat y = -h2 + i * density;
                verts.push_back (w2 + 1);
                verts.push_back (y);
                verts.push_back (-w2 - 1);
                verts.push_back (y);
        }

        glVertexPointer(2, GL_FLOAT, 0, &verts[0]);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glColor4f (gridColor.getR (), gridColor.getG (), gridColor.getB (), gridColor.getA ());
        glLineWidth (1);
        glDrawArrays (GL_LINES, 0, verts.size () / 2u);

        // Osie ukladu wsp.

        GLfloat verts1[] = {
                -w2 - 1, 0,
                w2 + 1, 0,
                0, -h2 - 1,
                0, h2 + 1
        };

        glVertexPointer (2, GL_FLOAT, 0, verts1);
        glColor4f (color.getR () - 0.1, color.getG () - 0.1, color.getB () - 0.1, color.getA ());
        glDrawArrays (GL_LINES, 0, 4);
}

} /* namespace View */
