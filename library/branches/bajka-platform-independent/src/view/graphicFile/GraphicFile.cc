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
#include <common/dataSource/DataSource.h>

namespace View {

void load (const char *path,
           void **data,
           int *width,
           int *height,
           int *visibleWidthOut,
           int *visibleHeightOut,
           ColorSpace *colorSpace,
           int *bitDepth,
           bool expandDimensions2)
{
        Common::DataSource ds;
        ds.open (path, Common::DataSource::MODE_UNKNOWN);

        if (checkIfPng (&ds)) {
                ds.rewind ();
                pngLoad (&ds, data, width, height, visibleWidthOut, visibleHeightOut, colorSpace, bitDepth, expandDimensions2);
                return;
        }

        ds.rewind ();

        if (checkIfJpeg (&ds)) {
                ds.rewind ();
                jpegLoad (&ds, data, width, height, visibleWidthOut, visibleHeightOut, colorSpace, bitDepth, expandDimensions2);
                return;
        }

        throw Util::OperationNotSupportedException (std::string ("load : unsupported file format. File : ") + path);
}

} /* namespace View */
