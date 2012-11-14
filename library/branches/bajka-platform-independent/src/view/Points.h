/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_POINTS_H_
#define BAJKA_VIEW_POINTS_H_

#include "Widget.h"
#include "draw/Color.h"

namespace View {

/**
 * Rysuje chmurę punktów.
 */
class Points : public Widget {
public:
        C__ (void)
        b_ ("Widget")

        Points () : size (1) {}
        virtual ~Points () {}

        virtual void update (Model::IModel *model, Event::UpdateEvent *e, Util::IShell *shell);

        Color const &getColor () const { return color; }
        m_ (setColor) void setColor (Color const &c) { color = c; }

        float getSize () const { return size; }
        m_ (setSize) void setSize (float f) { size = f; }

private:

        Color color;
        float size;

        E_ (Points)
};

} // namespace

#	endif /* PRIMITIVE_H_ */
