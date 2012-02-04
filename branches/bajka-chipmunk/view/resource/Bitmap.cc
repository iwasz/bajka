/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

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

} /* namespace View */
