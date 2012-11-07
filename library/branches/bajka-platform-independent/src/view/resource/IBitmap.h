/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_BITMAP_INTERFACE_H_
#define BAJKA_BITMAP_INTERFACE_H_

#include <core/Object.h>
#include "view/graphicFile/ColorSpace.h"
#include <cstddef>

namespace Geometry {
class Box;
}

namespace View {
class Color;

/**
 * Czyste dane bitmapowe - żadnego renderowania.
 */
class IBitmap : public Core::Object {
public:

        virtual ~IBitmap ()
        {
        }

        /**
         * Wkleja bitmapę source do tej (this) bitmapy. Kopiuje obszar srcRect ze źródła (lub całą, jeśli srcRect
         * jest NULL) i wkleja do tej (this) bitmapy w miejsce (x, y), lub w (0, 0)
         */
        virtual void paste (IBitmap *source, Geometry::Box const *srcRect = NULL, int x = 0, int y = 0) = 0;

        /**
         * Alokuje bitmapę.
         */
        virtual void allocate (int width, int height, ColorSpace cs) = 0;

        /**
         * Wypełnia całą bitmapę kolorem. Wolniejsza niż clear bez parametrów.
         */
        virtual void clear (View::Color const &color) = 0;

        /**
         * Wypełnia całą bitmapę RGB na czarno, a RGBA na przezroczysto. Szybka.
         */
        virtual void clear () = 0;

        /**
         * Format danych RGBA 8888.
         */
        virtual void *getData () = 0;

        /**
         * Rozmiar tego co jest widoczne, bo czasem bitmapy są rozciągnięte do potęg dwójki.
         */
        virtual int getVisibleWidth () const = 0;

        /**
         * Rozmiar tego co jest widoczne, bo czasem bitmapy są rozciągnięte do potęg dwójki.
         */
        virtual int getVisibleHeight () const = 0;

        /**
         * Fizyczny rozmiar bitmapy.
         */
        virtual int getWidth () const = 0;

        /**
         * Fizyczny rozmiar bitmapy.
         */
        virtual int getHeight () const = 0;

        /**
         *
         */
        virtual ColorSpace getColorSpace () const = 0;

        /**
         * Wielkość wiersza bitmapy w bajtach.
         */
        virtual size_t getPitch () const = 0;

};

} /* namespace View */

#endif /* BITMAP_H_ */
