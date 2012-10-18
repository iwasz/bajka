/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <GL/gl.h>
#include <GL/glut.h>
#include "GraphicsService.h"
#include "util/Exceptions.h"
#include "util/Math.h"
#include "util/Config.h"

/****************************************************************************/

void updateConfigViewport (Util::Config *config)
{
        if (config->autoViewport) {
                SDL_VideoInfo const *info = SDL_GetVideoInfo ();
                config->viewportWidth = info->current_w;
                config->viewportHeight = info->current_h;
        }

        if (config->autoProjection) {
                config->projectionWidth = config->viewportWidth;
                config->projectionHeight = config->viewportHeight;
        }
}

/****************************************************************************/

void initSdl (Util::Config *config)
{
        int flags;
        if (config->fullScreen) {
                flags = SDL_OPENGL | SDL_FULLSCREEN;
        }
        else {
                flags = SDL_OPENGL;
        }

        SDL_GL_SetAttribute (SDL_GL_RED_SIZE,   8);
        SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE,  8);
        SDL_GL_SetAttribute (SDL_GL_ALPHA_SIZE,  8);
        SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 16);

        if (!config->viewportWidth || !config->viewportHeight) {
                throw Util::InitException ("init : !viewportWidth || !viewportHeight");
        }

        /* Create a OpenGL screen */
        if (SDL_SetVideoMode (config->viewportWidth, config->viewportHeight, 0, flags) == NULL) {
                SDL_Quit ();
                throw Util::InitException (std::string ("init : Unable to create OpenGL screen : ") + SDL_GetError ());
        }

        /* Set the title bar in environments that support it */
        SDL_WM_SetCaption (config->windowCaption.c_str (), NULL);
        SDL_ShowCursor (config->showSystemCursor);
}

/****************************************************************************/

void freeSdl ()
{

}

/****************************************************************************/

SDL_Surface *createSurface (int w, int h)
{
        SDL_Surface *surface = SDL_CreateRGBSurface (SDL_SWSURFACE, w, h, 32,

        #if SDL_BYTEORDER == SDL_LIL_ENDIAN
                    0x000000FF,
                    0x0000FF00,
                    0x00FF0000,
                    0xFF000000
        #else
                    0xFF000000,
                    0x00FF0000,
                    0x0000FF00,
                    0x000000FF
        #endif
        );

        if (surface == NULL) {
                throw Util::RuntimeException ("expandSurfacePowerOf2 : surface == NULL");
        }

        return surface;
}

/****************************************************************************/

View::IBitmap *expandSurfacePowerOf2 (View::IBitmap *input, Geometry::Box const *region)
{
        return NULL;
}

/****************************************************************************/

void swapBuffers ()
{
        SDL_GL_SwapBuffers ();
}

/****************************************************************************/

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
//        gluOrtho2D (0, 0, viewportWidth, viewportHeight);

        float aspectRatio = double (config->viewportHeight) / config->viewportWidth;
        float rX = config->projectionWidth / 2;
        float rY;

        if (config->projectionHeight == 0) {
                rY = rX * aspectRatio;
                config->projectionHeight = rY * 2;
        }
        else {
                rY = config->projectionHeight / 2;
        }

        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
//        gluOrtho2D (-viewportWidth / 2.0, viewportWidth / 2.0, -viewportHeight / 2.0, viewportHeight / 2.0);
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

