/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_TEXT_H_
#define BAJKA_VIEW_TEXT_H_

#include "ReflectionMacros.h"
#include "resource/Font.h"
#include "Primitive.h"

namespace View {

class Text : public Primitive {
public:
        C__ (void)
        b_ ("Widget")

        virtual ~Text () {}

        /// Do the drawing.
        virtual void update (Model::IModel *model);

        Ptr <Font> getFont () const { return font; }
        s_ (setFont) void setFont (Ptr <Font> f) { font = f; }

        std::string getText () const { return text; }
        m_ (setText) void setText (std::string const &s) { text = s; }

private:

        Ptr <Font> font;
        std::string text;

        E_ (Text)
};

} /* namespace View */

#	endif /* TEXT_H_ */
