/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "FileBitmap.h"
#include "view/graphicFile/GraphicFile.h"

namespace View {

void FileBitmap::setPath (std::string const &p)
{
        path = p;
        int dummy;
        load (p.c_str (), &data, &width, &height, &visibleWidth, &visibleHeight, &colorSpace, &dummy, true);
}

/****************************************************************************/

FileBitmap::~FileBitmap ()
{
        // Usunięte będzie w Bitmap
}

} /* namespace View */
