/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_BITMAP_INTERFACE_H_
#define BAJKA_BITMAP_INTERFACE_H_

#include <Object.h>
#include "../../geometry/Box.h"

namespace View {

/**
 * Czyste dane bitmapowe - żadnego renderowania.
 */
class IBitmap : public Core::Object {
public:

        virtual ~IBitmap () {}

        /**
         * Format danych RGBA 8888.
         */
        virtual void *getData () = 0;

        virtual int getWidth () const = 0;
        virtual int getHeight () const = 0;

        /**
         * Tworzy nową, pustą bitmapę o rozmiarach destW x destH. Następnie kopiuje do niej
         * obszar srcRect z tej (this) bitmapy i wkleja go w górnym lewym rogu.
         * - Jeśli srcRect jest null, to kopiowany jest cały obszar źródłowej (tej) bitmapy.
         * - Jeśli destW jest równe -1, to domyślnie zostanie uzyta szerokość prostokąta źródłowego.
         * - Jeśli destH jest równe -1, to domyślnie zostanie uzyta wysokość prostokąta źródłowego.
         */
        virtual Ptr <IBitmap> blit (Geometry::Box const *srcRect = NULL, int destW = -1, int destH = -1) = 0;
};

} /* namespace View */

#endif /* BITMAP_H_ */
