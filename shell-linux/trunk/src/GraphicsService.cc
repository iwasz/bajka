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
#include "util/App.h"
#include "view/resource/Bitmap.h"

namespace View {

void GraphicsService::init (bool fullScreen,
                              int *resX,
                              int *resY,
                              std::string const &caption,
                              bool showSystemCursor)
{
        int flags;
        if (fullScreen) {
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

        if (!resX || !resY) {
                throw Util::InitException ("GraphicsService::init : !resX || !resY");
        }

        /* Create a OpenGL screen */
        if (SDL_SetVideoMode (*resX, *resY, 0, flags) == NULL) {
                SDL_Quit ();
                throw Util::InitException (std::string ("GraphicsService::init : Unable to create OpenGL screen : ") + SDL_GetError ());
        }

        /* Set the title bar in environments that support it */
        SDL_WM_SetCaption (caption.c_str (), NULL);

        SDL_ShowCursor (showSystemCursor);
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

IBitmap *GraphicsService::expandSurfacePowerOf2 (IBitmap *input, Geometry::Box const *region)
{
}

/****************************************************************************/

void GraphicsService::swapBuffers ()
{
        SDL_GL_SwapBuffers ();
}

} /* namespace View */
