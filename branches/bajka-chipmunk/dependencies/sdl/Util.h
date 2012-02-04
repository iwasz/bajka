/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SDL_UTIL_H_
#define BAJKA_SDL_UTIL_H_

#include <SDL.h>
#include "../../geometry/Box.h"

namespace Sdl {

/**
 * Rozszerza surface takj, żeby jego wys i szer były potęgami 2. Za skasowanie
 * zwróconego surface jest odpowiedzialny user.
 */
SDL_Surface *expandSurfacePowerOf2 (SDL_Surface *, Geometry::Box const *region = NULL);

}

#	endif /* UTIL_H_ */
