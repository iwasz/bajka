/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID
#include "GraphicsService.h"
#include "../../util/Exceptions.h"
#include "../../util/Math.h"
#include "../../util/App.h"

namespace View {

void GraphicsService::init (bool fullScreen,
                              int *resX,
                              int *resY,
                              std::string const &caption,
                              bool showSystemCursor)
{
}

/****************************************************************************/

void GraphicsService::free ()
{

}

/****************************************************************************/

//SDL_Surface *GraphicsService::createSurface (int w, int h)
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
//SDL_Surface *GraphicsService::expandSurfacePowerOf2 (SDL_Surface *input, Geometry::Box const *region)
//{
//        SDL_Surface *texSurface = NULL;
//
//        int origW, origH;
//
//        if (region) {
//                origW = region->getWidth ();
//                origH = region->getHeight ();
//        }
//        else {
//                origW = input->w;
//                origH = input->h;
//        }
//
//        // Podniesione do następnej potęgi
//        int width = Util::Math::nextSqr (origW);
//        int height = Util::Math::nextSqr (origH);
//
//        if (region || height != input->h || width != input->w) {
//
//                SDL_Surface *surface = createSurface (width, height);
//
//                Uint32 saved_flags = input->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
//
//                if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) {
//                        SDL_SetAlpha (input, 0, 0);
//                }
//
//                SDL_Rect destRct;
//
//                /* Copy the surface into the GL texture surface (texSurface) */
//                destRct.x = 0;
//                destRct.y = height - origH;
//
//                if (!region) {
//
//                        SDL_BlitSurface (input, NULL, surface, &destRct);
//                }
//                else {
//                        SDL_Rect srcRct;
//
//                        /* Copy the surface into the GL texture surface (texSurface) */
//                        srcRct.x = region->ll.x;
//                        srcRct.y = region->ll.y;
//                        srcRct.w = region->getWidth ();
//                        srcRct.h = region->getHeight ();
//
//                        SDL_BlitSurface (input, &srcRct, surface, &destRct);
//
//#if 0
//                        std::cerr << srcRct.x << "," << srcRct.y << "," << srcRct.w << "," << srcRct.h << ","
//                                << destRct.x << "," << destRct.y << "," << destRct.w << "," << destRct.h << std::endl;
//#endif
//                }
//
//                texSurface = surface;
//        }
//        else {
//                texSurface = input;
//        }
//
//        return texSurface;
//}

/****************************************************************************/

void GraphicsService::swapBuffers ()
{
}

} /* namespace View */

#endif
