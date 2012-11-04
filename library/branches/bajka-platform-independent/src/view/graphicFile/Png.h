/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_RESOURCES_PNG_H_
#define BAJKA_RESOURCES_PNG_H_

namespace View {

/**
 * Ładuje obrazek z pliku PNG w formacie RGBA 8888.
 */
extern void pngLoad (void *source, void **data, int *width, int *height, int *visibleWidthOut, int *visibleHeightOut, bool expandDimensions2);

/**
 * Sprawdza czy plik typu PNG.
 */
extern bool checkIfPng (void *source);

} // namespace

#endif /* PNG_H_ */
