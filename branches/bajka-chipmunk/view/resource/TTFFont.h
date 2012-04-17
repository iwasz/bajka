/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_SDL
#ifndef BAJKA_TTFFONT_H_
#define BAJKA_TTFFONT_H_

#include <SDL_ttf.h>
#include "ReflectionMacros.h"
#include "IFont.h"

namespace View {

class TTFFont : public IFont {
public:

        C__ (std::string const &)
        TTFFont (std::string const &path);

        C_ (std::string const &, int)
        TTFFont (std::string const &path, int ptSize);

        C_ (std::string const &, int, long int)
        TTFFont (std::string const &path, int ptSize, long int index);

        ~TTFFont ();

        enum Type {
                SOLID,
                SHADED,
                BLENDED
        };

        enum Style {
                NORMAL          = TTF_STYLE_NORMAL,
                BOLD            = TTF_STYLE_BOLD,
                ITALIC          = TTF_STYLE_ITALIC,
                UNDERLINE       = TTF_STYLE_UNDERLINE,
                STRIKETHROUGH   = TTF_STYLE_STRIKETHROUGH
        };

        // TODO Tu jest jakoś źle chyba.
        enum Hinting {
                FULL,
                LIGHT,
                MONO,
                NONE
        };

        Ptr <IBitmap> render (std::string const &text, View::Color const &fgColor, View::Color const &bgColor);
        Ptr <IBitmap> renderMulti (std::string const &text, View::Color const &fgColor, View::Color const &bgColor, TextAlign textAlign = LEFT);

        // TODO Typ zwracany powinien być Hinting
        int getHinting () const;
        m_ (setHinting) void setHinting (int hint);

        int getType () const { return type; }
        m_ (setType) void setType (int t) { type = t; }

        bool getUtf8 () const { return utf8; }
        m_ (setUtf8) void setUtf8 (bool b) { utf8 = b; }

        int getStyle () const;
        m_ (setStyle) void setStyle (int i);

        int getOutline () const;
        m_ (setOutline) void setOutline (int i);

        bool getKerning () const;
        m_ (setKerning) void setKerning (bool b);

private:

        void open (std::string const &path, int ptSize = -1, long int index = -1);

private:

        TTF_Font *font;
        int type; // TODO to powinno być typu Type
        bool utf8;

        E_ (TTFFont)
};

} /* namespace View */

#endif /* TTFFONT_H_ */
#endif
