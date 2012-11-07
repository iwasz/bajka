/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Bitmap.h"
#include "geometry/Box.h"
#include "view/draw/Color.h"

namespace View {

void Bitmap::paste (IBitmap *source, Geometry::Box const *srcRect, int x, int y)
{

}

/****************************************************************************/

void Bitmap::allocate (int width, int height, ColorSpace cs)
{

}

/****************************************************************************/

void Bitmap::clear (View::Color const &color)
{

}

//
//Ptr <View::IBitmap> Bitmap::blit (Geometry::Box const *region, int width, int height)
//{
//        int origW, origH;
//
//        if (region) {
//                origW = region->getWidth ();
//                origH = region->getHeight ();
//        }
//        else {
//                origW = getWidth ();
//                origH = getHeight ();
//        }
//
//        width = (width < 0) ? origW : width;
//        height = (height < 0) ? origH : height;
//
//        SDL_Surface *surface = createSurface (width, height);
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
//        destRct.y = height - origH;
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
//        return boost::make_shared <Bitmap> (surface);
//}

} // namespace
