/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANDROID
#ifndef BAJKA_BITMAP_INTERFACE_H_
#define BAJKA_BITMAP_INTERFACE_H_

#include <Object.h>

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
};

} /* namespace View */

#endif /* BITMAP_H_ */
#endif
