/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_TEXT_H_
#define BAJKA_VIEW_TEXT_H_

#include "openGl/OpenGl.h"
#include "util/ReflectionMacros.h"
#include "resource/IFont.h"
#include "Image.h"

namespace View {

class Text : public Image {
public:
        C__ (void)
        b_ ("Primitive")

        Text ();
        virtual ~Text ();

        IFont *getFont () const { return font; }
        void setFont (IFont *f) { font = f; }

        std::string getText () const { return text; }
        void setText (std::string const &s) { text = s; }

        bool getMultiline () const { return multiline; }
        void setMultiline (bool b) { multiline = b; }

        IFont::TextAlign getAlign () const { return align; }
        m_ (setAlign) void setAlign (int a) { align = (IFont::TextAlign)a; } // TODO typ na Align

        Color const &getForeground () const { return foreground; }
        m_ (setForeground) void setForeground (Color const &foreground) { this->foreground = foreground; }

        double getWidthHint () const;
        double getHeightHint () const;

protected:

        virtual void check ();

private:

        IFont *p_ (font);
        std::string p_ (text);
        std::size_t hash;
        bool p_ (multiline);
        IFont::TextAlign align;
        Color foreground;

        E_ (Text)
};

} /* namespace View */

#endif /* TEXT_H_ */
