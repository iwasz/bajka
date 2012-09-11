/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ClearScreen.h"
#include "openGl/OpenGl.h"

namespace View {

void ClearScreen::update (Model::IModel *, Event::UpdateEvent *e)
{
//        glMatrixMode (GL_MODELVIEW);
//        glLoadIdentity ();
        glClearColor (color.r, color.g, color.b, color.a);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} /* namespace View */
