/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_RESOURCE_JPEG_H_
#define BAJKA_RESOURCE_JPEG_H_

#include "ColorSpace.h"

namespace View {

/**
 * Ładuj JPEG.
 */
extern void jpegLoad (void *source,
                      void **data,
                      int *width,
                      int *height,
                      int *visibleWidthOut,
                      int *visibleHeightOut,
                      ColorSpace *colorSpace,
                      int *bitDepth,
                      bool expandDimensions2);

/**
 * Sprawdza czy plik typu JPEG.
 */
extern bool checkIfJpeg (void *source);

} /* namespace View */

#endif /* JPEG_H_ */
