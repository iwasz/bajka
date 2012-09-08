/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_FONT_H_
#define BAJKA_FONT_H_

#include <Object.h>
#include "IBitmap.h"
#include "view/draw/Color.h"

namespace View {

struct IFont : public Core::Object {

        enum TextAlign {
                LEFT,
                RIGHT,
                CENTER
        };

        virtual ~IFont () {}

        /**
         * Renderuj pojedynczą linię tekstu (nie rozumie znaków nowej linii).
         */
        virtual Ptr <IBitmap> render (std::string const &text, View::Color const &fgColor, View::Color const &bgColor) = 0;

        /**
         * Renderuj tekst w wielu liniach (akceptuje znaki nowej linii, oraz
         * umie wrapować tekst).
         */
        virtual Ptr <IBitmap> renderMulti (std::string const &text, View::Color const &fgColor, View::Color const &bgColor, TextAlign textAlign = LEFT) = 0;

};

} /* namespace View */

#endif /* TTFFONT_H_ */
