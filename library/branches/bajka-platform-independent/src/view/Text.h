/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANDROID
#ifndef BAJKA_VIEW_TEXT_H_
#define BAJKA_VIEW_TEXT_H_

#include "openGl/OpenGl.h"
#include "util/ReflectionMacros.h"
#include "resource/IFont.h"
#include "Primitive.h"

namespace View {

class Text : public Primitive {
public:
        C__ (void)
        b_ ("Primitive")

        Text () : font (NULL),
                hash (0),
                texWidth (0),
                texHeight (0),
                imgWidth (0),
                imgHeight (0),
                multiline (false),
                align (IFont::LEFT) {}

        virtual ~Text () {}

        /// Do the drawing.
        virtual void update (Model::IModel *model, Event::UpdateEvent *e);

        IFont *getFont () const { return font; }
        void setFont (IFont *f) { font = f; }

        std::string getText () const { return text; }
        void setText (std::string const &s) { text = s; }

        bool getMultiline () const { return multiline; }
        void setMultiline (bool b) { multiline = b; }

        IFont::TextAlign getAlign () const { return align; }
        m_ (setAlign) void setAlign (int a) { align = (IFont::TextAlign)a; } // TODO typ na Align

        double getWidthHint () const;
        double getHeightHint () const;

private:

        void init ();
        void initIf ();

private:

        IFont *p_ (font);
        std::string p_ (text);
        std::size_t hash;
        GLuint texName;
        // Rozmiary textury (potęga 2jki)
        int texWidth, texHeight;
        // Faktyczne rozmiary bitmapy (równe rozmiarom regionu, lub rozmiarom obrazka, jeśli region pusty).
        int imgWidth, imgHeight;
        bool p_ (multiline);
        IFont::TextAlign align;

        E_ (Text)
};

} /* namespace View */

#endif /* TEXT_H_ */
#endif
