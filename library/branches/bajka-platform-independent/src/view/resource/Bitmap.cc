/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#if 0
#ifdef USE_SDL
#include <SDL.h>
#include "Bitmap.h"
#include "util/Exceptions.h"

namespace View {

Bitmap::Bitmap (int width, int height)
{
        image = GraphicsService::createSurface (width, height);
}

/****************************************************************************/

void Bitmap::setPath (std::string const &p)
{
        path = p;
        image = IMG_Load (path.c_str ());
        assertThrow (image != NULL, "Image::init : couldn't load image : [" + path + "]");
}

/****************************************************************************/

Bitmap::~Bitmap ()
{
        SDL_FreeSurface (image);
}

/****************************************************************************/

int Bitmap::getWidth () const
{
        if (!image) {
                return -1;
        }

        return image->w;
}

/****************************************************************************/

int Bitmap::getHeight () const
{
        if (!image) {
                return -1;
        }

        return image->h;
}

/****************************************************************************/

//IBitmap *Bitmap::blit (IBitmap *dest, Geometry::Box const *region, int x, int y)
//{
//        int srcW, srcH;
//
//        if (region) {
//                srcW = region->getWidth ();
//                srcH = region->getHeight ();
//        }
//        else {
//                srcW = getWidth ();
//                srcH = getHeight ();
//        }
//
////        width = (width < 0) ? srcW : width;
////        height = (height < 0) ? srcH : height;
//
//        SDL_Surface *surface = static_cast <Bitmap *> (dest)->image;
//
//        Uint32 saved_flags = image->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
//
//        if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) {
//                SDL_SetAlpha (image, 0, 0);
//        }
//
//        SDL_Rect destRct;
//
//        /* Copy the surface into the GL texture surface (texSurface) */
//        destRct.x = 0;
//        destRct.y = height - srcH;
//
//        if (!region) {
//                SDL_BlitSurface (image, NULL, surface, &destRct);
//        }
//        else {
//                SDL_Rect srcRct;
//
//                /* Copy the surface into the GL texture surface (texSurface) */
//                srcRct.x = region->ll.x;
//                srcRct.y = region->ll.y;
//                srcRct.w = region->getWidth ();
//                srcRct.h = region->getHeight ();
//
//                SDL_BlitSurface (image, &srcRct, surface, &destRct);
//
//#if 0
//                std::cerr << srcRct.x << "," << srcRct.y << "," << srcRct.w << "," << srcRct.h << ","
//                        << destRct.x << "," << destRct.y << "," << destRct.w << "," << destRct.h << std::endl;
//#endif
//        }
//
//        return dest;
//
//}

Ptr <IBitmap> Bitmap::blit (Geometry::Box const *region, int width, int height)
{
        int origW, origH;

        if (region) {
                origW = region->getWidth ();
                origH = region->getHeight ();
        }
        else {
                origW = getWidth ();
                origH = getHeight ();
        }

        width = (width < 0) ? origW : width;
        height = (height < 0) ? origH : height;

        SDL_Surface *surface = GraphicsService::createSurface (width, height);

        Uint32 saved_flags = image->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);

        if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) {
                SDL_SetAlpha (image, 0, 0);
        }

        SDL_Rect destRct;

        /* Copy the surface into the GL texture surface (texSurface) */
        destRct.x = 0;
        destRct.y = height - origH;

        if (!region) {
                SDL_BlitSurface (image, NULL, surface, &destRct);
        }
        else {
                SDL_Rect srcRct;

                /* Copy the surface into the GL texture surface (texSurface) */
                srcRct.x = region->ll.x;
                srcRct.y = region->ll.y;
                srcRct.w = region->getWidth ();
                srcRct.h = region->getHeight ();

                SDL_BlitSurface (image, &srcRct, surface, &destRct);

#if 0
                std::cerr << srcRct.x << "," << srcRct.y << "," << srcRct.w << "," << srcRct.h << ","
                        << destRct.x << "," << destRct.y << "," << destRct.w << "," << destRct.h << std::endl;
#endif
        }

        return boost::make_shared <Bitmap> (surface);
}


} /* namespace View */
#endif
#endif
