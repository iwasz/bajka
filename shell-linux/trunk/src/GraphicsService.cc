/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <view/openGl/OpenGl.h>
#include <util/Exceptions.h>
#include "GraphicsService.h"
#include <Platform.h>
#include <util/Config.h>
#include <SDL.h>
#include <view/freetype/Freetype.h>

namespace U = Util;

/****************************************************************************/

GraphicsService::GraphicsService ()
{
}

/****************************************************************************/

bool GraphicsService::initDisplay (Util::Config *config)
{
        Uint32 subsystemInit = SDL_WasInit (SDL_INIT_EVERYTHING);

        if (subsystemInit & SDL_INIT_VIDEO) {
                return true;
        }

        /* Initialize SDL for video output */
        if (SDL_Init (SDL_INIT_VIDEO) < 0) {
                throw U::InitException ("Unable to initialize SDL : " + std::string (SDL_GetError ()));
        }

        if (ttfInit () < 0) {
                throw U::InitException ("TTF_Init failed");
        }

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

        return true;
}

/****************************************************************************/

void GraphicsService::termDisplay ()
{
        ttfQuit ();
        SDL_Quit ();
        printlog ("GraphicsService::termDisplay : done.");
}

/****************************************************************************/

void GraphicsService::unbindSurfaceAndContext ()
{
        printlog ("GraphicsService::unbindSurfaceAndContext : done.");
}

/****************************************************************************/

bool GraphicsService::saveScreenDimensionsInConfig (Util::Config *config)
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

        printlog ("GraphicsService::saveScreenDimensionsInConfig : w=%d, h=%d, autoProjection=%d.", config->viewportWidth, config->viewportHeight, config->autoProjection);
        return true;
}

/****************************************************************************/

void GraphicsService::swapBuffers ()
{
        SDL_GL_SwapBuffers ();
}
