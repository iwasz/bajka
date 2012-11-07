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

        Bitmap () : data (NULL), width (0), height (0), visibleWidth (0), visibleHeight (0), bitDepth (0), colorSpace (RGBA)  {}
        virtual ~Bitmap () {}

        void paste (IBitmap *source, Geometry::Box const *srcRect = NULL, int x = 0, int y = 0);
        void allocate (int width, int height, ColorSpace cs);
        void clear (View::Color const &color);

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

        int getBitDepth () const { return bitDepth; }
        void setBitDepth (int i) { bitDepth = i; }

        ColorSpace getColorSpace () const { return colorSpace; }
        void setColorSpace (ColorSpace i) { colorSpace = i; }

protected:

        void *data;
        int width;
        int height;
        int visibleWidth;
        int visibleHeight;
        int bitDepth;
        ColorSpace colorSpace;
};

} // namespace

#endif
