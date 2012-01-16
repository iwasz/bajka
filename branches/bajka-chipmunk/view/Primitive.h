/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_PRIMITIVE_H_
#define BAJKA_VIEW_PRIMITIVE_H_

#include "Widget.h"
#include "draw/Color.h"

namespace View {

class Primitive : public Widget {
public:
        d__
        b_ ("Widget")

        virtual ~Primitive () {}

        Color const &getBackground () const { return background; }
        m_ (setBackground) void setBackground (Color const &background) { this->background = background; }
        m_ (setBackground2) void setBackground2 (Ptr <Color> c) { this->background = *c; }

        Color const &getForeground () const { return foreground; }
        m_ (setForeground) void setForeground (Color const &foreground) { this->foreground = foreground; }

private:

        Color foreground;
        Color background;

        E_ (Primitive)
};

} // namespace

#	endif /* PRIMITIVE_H_ */
