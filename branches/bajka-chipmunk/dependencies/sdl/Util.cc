/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Util.h"
#include "../../util/Exceptions.h"
#include "../../util/Math.h"

namespace Sdl {

SDL_Surface *expandSurfacePowerOf2 (SDL_Surface *input)
{
        SDL_Surface *texSurface = NULL;

        // Podniesione do następnej potęgi
        unsigned int width = Util::Math::nextSqr (input->w);
        unsigned int height = Util::Math::nextSqr (input->h);

        if (height != input->h || width != input->w) {

                SDL_Surface *surface = SDL_CreateRGBSurface (SDL_SWSURFACE, width, height, 32,
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

                Uint32 saved_flags = input->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
                if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) {
                        SDL_SetAlpha (input, 0, 0);
                }

                /* Copy the surface into the GL texture surface (texSurface) */
                SDL_Rect area;

                area.x = 0;
                area.y = height - input->h;
                area.w = input->w;
                area.h = input->h;

                SDL_BlitSurface (input, NULL, surface, &area);
//                SDL_FreeSurface (input);

                texSurface = surface;
        }
        else {
                texSurface = input;
        }

        return texSurface;
}

} /* namespace Sdl */
