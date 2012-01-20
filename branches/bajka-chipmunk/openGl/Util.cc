/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "Util.h"

namespace View {

void Util::mouseToDisplay (int x, int y, int windowWidth, int windowHeight, double *nx, double *ny)
{
        GLdouble model[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, model);

        GLdouble proj[16];
        glGetDoublev(GL_PROJECTION_MATRIX, proj);

        GLint view[4];
        glGetIntegerv(GL_VIEWPORT, view);

        GLdouble mz;
        gluUnProject(x, windowHeight - y, 0.0f, model, proj, view, nx, ny, &mz);
}

} /* namespace View */
