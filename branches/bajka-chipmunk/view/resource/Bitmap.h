/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANDROID
#ifndef BAJKA_BITMAP_H_
#define BAJKA_BITMAP_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "../../util/ReflectionMacros.h"
#include "IBitmap.h"

namespace View {

/**
 * Bitmapa z pliku.
 */
class Bitmap : public IBitmap {
public:

        C__ (void)
        Bitmap (SDL_Surface *i = NULL) : image (i) {}
        virtual ~Bitmap ();

        std::string const &getPath () const { return path; }
        m_ (setPath) void setPath (std::string const &p);

        void *getData () { return image; }

        int getWidth () const;
        int getHeight () const;

        Ptr <IBitmap> blit (Geometry::Box const *srcRect = NULL, int destW = -1, int destH = -1);

private:

        std::string path;
        SDL_Surface *image;

        E_ (Bitmap)
};

} /* namespace View */

#endif /* BITMAP_H_ */
#endif
