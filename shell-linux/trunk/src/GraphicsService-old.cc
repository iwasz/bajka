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
#include <view/freetype/Freetype.h>

/****************************************************************************/

void updateConfigViewport (Util::Config *config)
{

}

/****************************************************************************/

void initSdl (Util::Config *config)
{
}

/****************************************************************************/

void freeSdl ()
{

}

/****************************************************************************/

//SDL_Surface *createSurface (int w, int h)
//{
//        SDL_Surface *surface = SDL_CreateRGBSurface (SDL_SWSURFACE, w, h, 32,
//
//        #if SDL_BYTEORDER == SDL_LIL_ENDIAN
//                    0x000000FF,
//                    0x0000FF00,
//                    0x00FF0000,
//                    0xFF000000
//        #else
//                    0xFF000000,
//                    0x00FF0000,
//                    0x0000FF00,
//                    0x000000FF
//        #endif
//        );
//
//        if (surface == NULL) {
//                throw Util::RuntimeException ("expandSurfacePowerOf2 : surface == NULL");
//        }
//
//        return surface;
//}
//
///****************************************************************************/
//
//View::IBitmap *expandSurfacePowerOf2 (View::IBitmap *input, Geometry::Box const *region)
//{
//        return NULL;
//}

/****************************************************************************/

void swapBuffers ()
{
}


