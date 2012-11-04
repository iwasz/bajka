/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef _BAJKA_BITMAP_H_
#define _BAJKA_BITMAP_H_

#include <string>
#include "util/ReflectionMacros.h"
#include "view/resource/IBitmap.h"

namespace View {

/**
 * Bitmapa z pliku.
 */
class Bitmap : public View::IBitmap {
public:

        C__ (void)
        Bitmap () : data (NULL), width (0), height (0), visibleWidth (0), visibleHeight (0)  {}
        virtual ~Bitmap ();

        std::string const &getPath () const { return path; }
        m_ (setPath) void setPath (std::string const &p);

        void *getData () { return data; }
        int getVisibleWidth () const { return visibleWidth; }
        int getVisibleHeight () const { return visibleHeight; }
        int getWidth () const { return width; }
        int getHeight () const { return height; }

private:

        std::string path;
        void *data;
        int width;
        int height;
        int visibleWidth;
        int visibleHeight;

        E_ (Bitmap)
};

} // namespace

#endif
