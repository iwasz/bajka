/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_RESOURCES_GRAPHICFILE_H_
#define BAJKA_RESOURCES_GRAPHICFILE_H_

#include "Png.h"
#include "Jpeg.h"
#include "ColorSpace.h"

namespace View {

extern void load (const char *path,
                  void **data,
                  int *width,
                  int *height,
                  int *visibleWidthOut,
                  int *visibleHeightOut,
                  ColorSpace *colorSpace,
                  int *bitDepth,
                  bool expandDimensions2);

} /* namespace View */

#endif /* GRAPHICFILE_H_ */
