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
#include "openGl/OpenGl.h"
#include "geometry/Box.h"

namespace Util {
class Config;
}

namespace View {
class IBitmap;
}

extern void updateConfigViewport (Util::Config *config);

/**
 * Inicjuje SDL.
 * @param fullScreen
 * @param viewportWidth
 * @param viewportHeight
 * @param caption
 */
extern void initSdl (Util::Config *config);

/**
 * Wyłącza SDL.
 */
extern void freeSdl ();

/**
 * Tworzy SDL surface z domyślnymi dla bajki parametrami.
 */
extern SDL_Surface *createSurface (int w, int h);

/**
 * Rozszerza surface takj, żeby jego wys i szer były potęgami 2. Za skasowanie
 * zwróconego surface jest odpowiedzialny user.
 */
extern View::IBitmap *expandSurfacePowerOf2 (View::IBitmap *, Geometry::Box const *region = NULL);

extern void initOpenGl (Util::Config *config);
extern void freeOpenGl ();
extern void mouseToDisplay (int x, int y, int windowWidth, int windowHeight, float *nx, float *ny);

#endif /* GRAPHICSINTERFACE_H_ */
