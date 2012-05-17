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

        Primitive () : thickness (0), prettyJoin (false) {}
        virtual ~Primitive () {}
        virtual void update (Model::IModel *model, Event::UpdateEvent *e);

        Color const &getBackground () const { return background; }
        m_ (setBackground) void setBackground (Color const &background) { this->background = background; }

        Color const &getForeground () const { return foreground; }
        m_ (setForeground) void setForeground (Color const &foreground) { this->foreground = foreground; }

        /**
         * Grubość linii w pixelach.
         */
        float getThickness () const { return thickness; }
        m_ (setThickness) void setThickness (float t) { thickness = t; }

        bool getPrettyJoin () const { return prettyJoin; }
        m_ (setPrettyJoin) void setPrettyJoin (bool b) { prettyJoin = b; }

private:

        Color foreground;
        Color background;
        float thickness;
        bool prettyJoin;

        E_ (Primitive)
};

} // namespace

#	endif /* PRIMITIVE_H_ */
