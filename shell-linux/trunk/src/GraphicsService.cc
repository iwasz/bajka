/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "GraphicsService.h"
#include "util/Exceptions.h"
#include "util/Math.h"
#include "util/Config.h"

void GraphicsService::init (Util::Config *config)
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
                throw Util::InitException ("GraphicsService::init : !viewportWidth || !viewportHeight");
        }

        /* Create a OpenGL screen */
        if (SDL_SetVideoMode (config->viewportWidth, config->viewportHeight, 0, flags) == NULL) {
                SDL_Quit ();
                throw Util::InitException (std::string ("GraphicsService::init : Unable to create OpenGL screen : ") + SDL_GetError ());
        }

        /* Set the title bar in environments that support it */
        SDL_WM_SetCaption (config->windowCaption.c_str (), NULL);
        SDL_ShowCursor (config->showSystemCursor);
}

/****************************************************************************/

void GraphicsService::free ()
{

}

/****************************************************************************/

SDL_Surface *GraphicsService::createSurface (int w, int h)
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

View::IBitmap *GraphicsService::expandSurfacePowerOf2 (View::IBitmap *input, Geometry::Box const *region)
{
}

/****************************************************************************/

void swapBuffers ()
{
        SDL_GL_SwapBuffers ();
}
