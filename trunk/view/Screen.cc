/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "Screen.h"

namespace View {

void Screen::setModel (Ptr <Model::IModel> m)
{
        AbstractWidget::setModel (m);
        model = dynamic_pointer_cast <Model::Primitive> (m);
        assert (model);
}

/****************************************************************************/

void Screen::doDraw ()
{
        glClearColor (model->getFillColor ().getR (), model->getFillColor ().getG (),
                        model->getFillColor ().getB (), 1.0);

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/****************************************************************************/

void Screen::preDraw ()
{
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity ();
}

/****************************************************************************/

void Screen::postDraw ()
{
        glFlush ();
        // swap buffers to display, since we're double buffered.
        SDL_GL_SwapBuffers ();
}

}
