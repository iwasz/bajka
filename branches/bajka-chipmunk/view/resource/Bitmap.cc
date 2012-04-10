/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANDROID
#include "Bitmap.h"
#include "../../util/Exceptions.h"

namespace View {

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

} /* namespace View */
#endif
