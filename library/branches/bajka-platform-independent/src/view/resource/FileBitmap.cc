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
        load (p.c_str (), &data, &width, &height, &visibleWidth, &visibleHeight, &colorSpace, &bitDepth, true);
}

/****************************************************************************/

FileBitmap::~FileBitmap ()
{
        free (data);
}

} /* namespace View */
