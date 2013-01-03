/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_PNG
#ifndef BAJKA_RESOURCES_PNG_H_
#define BAJKA_RESOURCES_PNG_H_

#include "ColorSpace.h"
#include <common/dataSource/DataSource.h>

namespace View {

/**
 * Ładuje obrazek z pliku PNG w formacie RGBA 8888.
 */
extern void pngLoad (Common::DataSource *source,
                     void **data,
                     int *width,
                     int *height,
                     int *visibleWidthOut,
                     int *visibleHeightOut,
                     ColorSpace *colorSpace,
                     int *bitDepth,
                     bool expandDimensions2);

/**
 * Sprawdza czy plik typu PNG.
 */
extern bool checkIfPng (Common::DataSource *source);

} // namespace

#endif /* PNG_H_ */
#endif
