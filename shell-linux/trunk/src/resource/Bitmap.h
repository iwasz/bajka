/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_BITMAP_H_
#define BAJKA_BITMAP_H_

#include <string>
#include "util/ReflectionMacros.h"
#include "view/resource/IBitmap.h"

struct SDL_Surface;

/**
 * Bitmapa z pliku.
 */
class Bitmap : public View::IBitmap {
public:

        C__ (void)
        Bitmap (SDL_Surface *i = NULL) : image (i) {}
        Bitmap (int width, int height);
        virtual ~Bitmap ();

        std::string const &getPath () const { return path; }
        m_ (setPath) void setPath (std::string const &p);

        void *getData ();

        int getWidth () const;
        int getHeight () const;

        Ptr <View::IBitmap> blit (Geometry::Box const *srcRect = NULL, int destW = -1, int destH = -1);
//        IBitmap *blit (IBitmap *dest, Geometry::Box const *srcRect = NULL, int destW = -1, int destH = -1);

private:

        std::string path;
        SDL_Surface *image;

        E_ (Bitmap)
};

#endif
