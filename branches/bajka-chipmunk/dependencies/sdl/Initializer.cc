/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include "Initializer.h"
#include "../util/Exceptions.h"

namespace Util {

Initializer::Initializer()
{
        /* Initialize SDL for video output */
        if (SDL_Init (SDL_INIT_VIDEO) < 0) {
                throw InitException ("Unable to initialize SDL : " + std::string (SDL_GetError ()));
        }

        if (TTF_Init () < 0) {
            throw InitException ("TTF_Init failed");
        }
}

} /* namespace Util */

#endif
