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
        C__ (void)
        b_ ("Widget")

        virtual ~Primitive () {}
        virtual void update (Model::IModel *model, Event::UpdateEvent *e);

        Color const &getBackground () const { return background; }
        m_ (setBackground) void setBackground (Color const &background) { this->background = background; }

        Color const &getForeground () const { return foreground; }
        m_ (setForeground) void setForeground (Color const &foreground) { this->foreground = foreground; }

private:

        Color foreground;
        Color background;

        E_ (Primitive)
};

} // namespace

#	endif /* PRIMITIVE_H_ */
