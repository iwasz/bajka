/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SDL_GRAPHICSINTERFACE_H_
#define SDL_GRAPHICSINTERFACE_H_

#include <SDL.h>
#include "geometry/Box.h"

namespace Util {
class Config;
}

namespace View {
class IBitmap;
}

struct GraphicsService {

        /**
         * Inicjuje SDL.
         * @param fullScreen
         * @param viewportWidth
         * @param viewportHeight
         * @param caption
         */
        static void init (Util::Config *config);

        /**
         * Wyłącza SDL.
         */
        static void free ();

        /**
         * Tworzy SDL surface z domyślnymi dla bajki parametrami.
         */
        static SDL_Surface *createSurface (int w, int h);

        /**
         * Rozszerza surface takj, żeby jego wys i szer były potęgami 2. Za skasowanie
         * zwróconego surface jest odpowiedzialny user.
         */
        static View::IBitmap *expandSurfacePowerOf2 (View::IBitmap *, Geometry::Box const *region = NULL);


};

#endif /* GRAPHICSINTERFACE_H_ */
