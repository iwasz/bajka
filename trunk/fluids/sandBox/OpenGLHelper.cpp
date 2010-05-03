/****************************************************************************
 *                                                                          *
 *  Author & Copyright (c) :  Lukasz Iwaszkiewicz                           *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~  lukasz.iwaszkiewicz@gmail.com                 *
 *                                                                          *
 *  Date :                    Nov 4, 2009                                   *
 *  ~~~~~~                                                                  *
 *                                                                          *
 *      This program is free software;  you can redistribute it and / or    *
 *      modify it under the terms of the GNU General Public License. See    *
 *      COPYING file for details.                                           *
 *                                                                          *
 ****************************************************************************/
#if 0
#include "OpenGLHelper.h"

#ifdef BUILD_CUDA
#       include "fluid_system_host.cuh"
#endif
#       include "fluid_system.h"
#include "gl_helper.h"

#ifdef _MSC_VER // Windows
#       include <gl/glut.h>
#else // Linux
#       include <GL/glut.h>
#endif

/****************************************************************************/

void OpenGLDisplay::init (int argc, char **argv)
{
#ifdef BUILD_CUDA
        // Initialize CUDA
        cudaInit( argc, argv );
#endif

        // set up the window
        glutInit (&argc, &argv[0]);
        glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowPosition (100, 100);
        glutInitWindowSize ((int) window_width, (int) window_height);
        glutCreateWindow ("Fluids v.1 (c) 2008, R. Hoetzlein (ZLib)");

        glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
        glHint (GL_POLYGON_SMOOTH_HINT, GL_NICEST);

        srand (time (0x0));

        glClearColor (0.49, 0.49, 0.49, 1.0);
        glShadeModel (GL_SMOOTH);

        glEnable (GL_COLOR_MATERIAL);
        glEnable (GL_DEPTH_TEST);
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask (1);
        glEnable (GL_TEXTURE_2D);
}

/****************************************************************************/

void OpenGLDisplay::drawParticles (const std::vector<GeomBuf> &mBuf, int NumPoints)
{
        // View matricies
        float view_matrix[16]; // View matrix (V)
        float model_matrix[16]; // Model matrix (M)
        float proj_matrix[16]; // Projective matrix

        glEnable (GL_DEPTH_TEST);

        // Render depth map shadows
        glClearColor (0, 0, 0, 0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable (GL_CULL_FACE);
        glShadeModel (GL_SMOOTH);

        // ---- Create projection matrix for eye-coordinate transformations
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        // 35, to był parametr cam_fov i nie wiem co to jest.
        gluPerspective (35, window_width / (float) window_height, 10.0, 800.0);
        glPushMatrix ();
        glGetFloatv (GL_MODELVIEW_MATRIX, proj_matrix);
        glPopMatrix ();

        //computeView
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity ();
        /*
         * Poniższe parametry definiują kamerę jak można się domyślić i
         * były obliczane real time na podstawie ruchów myszy. Teraz
         * ustawiłem kamerę prosto do przodu, odsuniętą o 100.
         */
        gluLookAt (0, -100, 0, 0, 0, 0, 0, 0, 1);
        glPushMatrix ();
        glGetFloatv (GL_MODELVIEW_MATRIX, view_matrix);
        glPopMatrix ();

        // Draw 3D
        glEnable (GL_LIGHTING);
        glLoadMatrixf (view_matrix);
        glDisable (GL_LIGHTING);

/*--------------------------------------------------------------------------*/

        // Draw particles
//      psys.Draw (&view_matrix[0], 0.55);

        char* dat;
        Point* p;

        glEnable (GL_NORMALIZE);
        glLoadMatrixf (view_matrix);

        dat = mBuf[0].data;

        /*
         * Iteruj przez wszystkie punkty - punktów jest w mojej symulacji tylko 400.
         * I bardzo szczęśliwe jest to, że końcowy odbiorca dostaje do dyspozycji
         * (prawie-wektor) obiektów Point.
         */
        for (int n = 0; n < NumPoints; n++) {

                p = (Point*) dat;
                glPushMatrix ();
                // Przykładowe pos jednego z punktów : {x = 0.318198085, y = -12.8199997, z = 29.6597519}
                glTranslatef (p->pos.x, p->pos.y, p->pos.z);
                glScalef (0.2, 0.2, 0.2);
                glColor4f (RED(p->clr), GRN(p->clr), BLUE(p->clr), ALPH(p->clr));
                drawSphere ();
                glPopMatrix ();

                dat += mBuf[0].stride;
        }

/*--------------------------------------------------------------------------*/

        // Swap buffers
        glutSwapBuffers ();
        glutPostRedisplay ();
}
#endif
