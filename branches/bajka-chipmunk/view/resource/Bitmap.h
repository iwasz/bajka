/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_BITMAP_H_
#define BAJKA_BITMAP_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "../../util/ReflectionMacros.h"
#include "IBitmap.h"

namespace View {

class Bitmap : public IBitmap {
public:

        C__ (void)
        Bitmap () : image (NULL) {}
        virtual ~Bitmap ();

        std::string const &getPath () const { return path; }
        m_ (setPath) void setPath (std::string const &p);

        void *getData () { return image; }

private:

        std::string path;
        SDL_Surface *image;

        E_ (Bitmap)
};

} /* namespace View */

#	endif /* BITMAP_H_ */
