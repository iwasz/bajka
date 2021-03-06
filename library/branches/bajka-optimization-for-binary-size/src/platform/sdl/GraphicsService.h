/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_SDL
#ifndef SDL_GRAPHICSINTERFACE_H_
#define SDL_GRAPHICSINTERFACE_H_

#include <SDL.h>
#include "../../geometry/Box.h"

namespace View {
class IBitmap;

struct GraphicsService {

        /**
         * Inicjuje SDL.
         * @param fullScreen
         * @param resX
         * @param resY
         * @param caption
         */
        static void init (bool fullScreen,
                          int *resX,
                          int *resY,
                          std::string const &caption,
                          bool showSystemCursor);

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
        static IBitmap *expandSurfacePowerOf2 (IBitmap *, Geometry::Box const *region = NULL);

        static void swapBuffers ();

};

} /* namespace View */

#endif /* GRAPHICSINTERFACE_H_ */
#endif
