/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_RESOURCE_FILEBITMAP_H_
#define BAJKA_RESOURCE_FILEBITMAP_H_

#include <string>
#include "Bitmap.h"
#include "util/ReflectionMacros.h"

namespace View {

/**
 * Bitmapa, ktora sama ładuje się z pliku.
 */
class FileBitmap : public Bitmap {
public:

        C__ (void)

        FileBitmap () {}
        virtual ~FileBitmap ();

        std::string const &getPath () const { return path; }
        m_ (setPath) void setPath (std::string const &p);

private:

        std::string path;

        E_ (FileBitmap)
};

} /* namespace View */
#endif /* FILEBITMAP_H_ */
