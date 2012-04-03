/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID
#ifndef ANDROID_GRAPHICSINTERFACE_H_
#define ANDROID_GRAPHICSINTERFACE_H_

#include "../../geometry/Box.h"

namespace View {

struct GraphicsInterface {

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
//        static SDL_Surface *createSurface (int w, int h);

        /**
         * Rozszerza surface takj, żeby jego wys i szer były potęgami 2. Za skasowanie
         * zwróconego surface jest odpowiedzialny user.
         */
//        static SDL_Surface *expandSurfacePowerOf2 (SDL_Surface *, Geometry::Box const *region = NULL);

        static void swapBuffers ();

};

} /* namespace View */

#endif /* GRAPHICSINTERFACE_H_ */
#endif
