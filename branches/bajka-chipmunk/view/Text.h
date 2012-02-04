/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_TEXT_H_
#define BAJKA_VIEW_TEXT_H_

#include <SDL_opengl.h>
#include "ReflectionMacros.h"
#include "resource/IFont.h"
#include "Primitive.h"

namespace View {

class Text : public Primitive {
public:
        C__ (void)
        b_ ("Widget")

        Text () : hash (0) {}
        virtual ~Text () {}

        /// Do the drawing.
        virtual void update (Model::IModel *model);

        Ptr <IFont> getFont () const { return font; }
        S_ (setFont) void setFont (Ptr <IFont> f) { font = f; }

        std::string getText () const { return text; }
        m_ (setText) void setText (std::string const &s) { text = s; }

private:

        void init (Model::IModel *model);

private:

        Ptr <IFont> font;
        std::string text;
        std::size_t hash;
        GLuint texName;
        int texWidth, texHeight;

        E_ (Text)
};

} /* namespace View */

#	endif /* TEXT_H_ */
