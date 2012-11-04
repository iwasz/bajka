/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "GraphicFile.h"
#include "util/Exceptions.h"
#include <cstdio>

namespace View {

void load (const char *path, void **data, int *width, int *height, int *visibleWidthOut, int *visibleHeightOut, bool expandDimensions2)
{
        FILE *fp;

        if ((fp = fopen (path, "rb")) == NULL) {
                throw Util::InitException (std::string ("load : couldn't open grephic file : ") + path);
        }

        if (checkIfPng (fp)) {
                rewind (fp);
                pngLoad (fp, data, width, height, visibleWidthOut, visibleHeightOut, expandDimensions2);
                return;
        }

        rewind (fp);

        if (checkIfJpeg (fp)) {
                rewind (fp);
                jpegLoad (fp, data, width, height, visibleWidthOut, visibleHeightOut, expandDimensions2);
                return;
        }

        throw Util::OperationNotSupportedException (std::string ("load : unsupported file format. File : ") + path);
}

} /* namespace View */
