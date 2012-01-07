/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL.h>
#include <SDL_opengl.h>

#include "CustomRect.h"
#include "../model/Box.h"

void CustomRect::doDraw ()
{
        if (fill) {
                glColor3f (0.0, 0.0, 1.0);
                glBegin (GL_POLYGON);
        }
        else {
                glColor3f (1.0, 0.0, 0.0);
                glBegin (GL_POLYGON);
        }

                glVertex2f (box->getX1 (), box->getY1 ());
                glVertex2f (box->getX1 (), box->getY2 ());
                glVertex2f (box->getX2 (), box->getY2 ());
                glVertex2f (box->getX2 (), box->getY1 ());
        glEnd ();
}
