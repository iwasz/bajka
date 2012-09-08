/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <GL/gl.h>
#include <GL/glut.h>
#include "OpenGlService.h"
#include "util/Config.h"

void initOpenGl (Util::Config *config)
{
        glShadeModel(GL_FLAT);
        glDisable (GL_DEPTH_TEST);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        /*
         * Alpha blending. Niestety tekstura jest w niektorych miejscach
         * przezroczysta, ale wystaje spodniej niebieski kolor prostokątu.
         */
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Transformacje.
//        glMatrixMode (GL_MODELVIEW);
//        glLoadIdentity ();
//        gluOrtho2D (0, 0, resX, resY);

        float aspectRatio = double (config->resY) / config->resX;
        float rX = 100.0;
        float rY = rX * aspectRatio;

        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
//        gluOrtho2D (-resX / 2.0, resX / 2.0, -resY / 2.0, resY / 2.0);
        gluOrtho2D (-rX, rX, -rY, rY);

//        glEnable(GL_LINE_SMOOTH);
//        glEnable(GL_POINT_SMOOTH);
//        glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
//        glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);


        glPointSize (3);

        // glDrawArrays
        glEnableClientState(GL_VERTEX_ARRAY);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        /*
         * Te dwie poniższe komendy ustawiają filtrowanie dla przybliżania i
         * oddalania. GL_NEAREST - kolor z 1 teksela najbliższego pixelowi.
         */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/****************************************************************************/

void freeOpenGl ()
{

}

/****************************************************************************/

void mouseToDisplay (int x, int y, int windowWidth, int windowHeight, float *nx, float *ny)
{
        GLdouble model[16];
        glGetDoublev (GL_MODELVIEW_MATRIX, model);

        GLdouble proj[16];
        glGetDoublev (GL_PROJECTION_MATRIX, proj);

        GLint view[4];
        glGetIntegerv (GL_VIEWPORT, view);

        GLdouble mx, my, mz;
        gluUnProject(x, windowHeight - y, 0.0f, model, proj, view, &mx, &my, &mz);
        *nx = mx;
        *ny = my;
}
