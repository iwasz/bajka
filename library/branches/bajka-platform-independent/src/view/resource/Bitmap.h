/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef _BAJKA_BITMAP_H_
#define _BAJKA_BITMAP_H_

#include "view/resource/IBitmap.h"

namespace View {

/**
 * Bitmapa z pliku.
 */
class Bitmap : public View::IBitmap {
public:

        Bitmap () : data (NULL), width (0), height (0), visibleWidth (0), visibleHeight (0), colorSpace (RGBA)  {}
        virtual ~Bitmap ();

        enum { BIT_DEPTH = 8 };

        void paste (IBitmap *source, Geometry::Box const *srcRect = NULL, int x = 0, int y = 0);
        void allocate (int width, int height, ColorSpace cs);
        void clear (View::Color const &color);
        void clear ();

        void *getData () { return data; }
        void setData (void *d) { data = d; }

        int getVisibleWidth () const { return visibleWidth; }
        void setVisibleWidth (int i) { visibleWidth = i; }

        int getVisibleHeight () const { return visibleHeight; }
        void setVisibleHeight (int i) { visibleHeight = i; }

        int getWidth () const { return width; }
        void setWidth (int i) { width = i; }

        int getHeight () const { return height; }
        void setHeight (int i) { height = i; }

        ColorSpace getColorSpace () const { return colorSpace; }
        void setColorSpace (ColorSpace i) { colorSpace = i; }

        size_t getPitch () const { return (colorSpace == RGB) ? (width * 3) : (width * 4); }

protected:

        void *data;
        int width;
        int height;
        int visibleWidth;
        int visibleHeight;
        ColorSpace colorSpace;
};

} // namespace

#endif
