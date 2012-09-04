/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#if defined (USE_OPENGL) || defined (USE_OPENGLES)
#include "OpenGlCommonService.h"
#include "OpenGl.h"

namespace View {

void OpenGlCommonService::clear (View::Color const &c)
{
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity ();
        glClearColor (c.r, c.g, c.b, c.a);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} /* namespace View */

#endif
