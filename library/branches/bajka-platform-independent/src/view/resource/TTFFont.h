/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_FREETYPE
#ifndef BAJKA_TTFFONT_H_
#define BAJKA_TTFFONT_H_

#include "util/ReflectionMacros.h"
#include "view/resource/IFont.h"

struct TTF_Font;

namespace Common {
class DataSource;
}

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
                BLENDED
        };

        // TODO To jest skopiowane z SDL/SDL_ttf, żeby nie inkludowac nagłówków z SDL. Dzięki temu program klienta nie musi miec zależności do SDL.
        enum Style {
                NORMAL          = 0x00,
                BOLD            = 0x01,
                ITALIC          = 0x02
        };

        // TODO Tu jest jakoś źle chyba.
        enum Hinting {
                FULL,
                LIGHT,
                MONO,
                NONE
        };

        Ptr <IBitmap> render (std::string const &text, View::Color const &fgColor);
        Ptr <IBitmap> renderMulti (std::string const &text, View::Color const &fgColor, TextAlign textAlign = LEFT);

        // TODO Typ zwracany powinien być Hinting
        int getHinting () const;
        m_ (setHinting) void setHinting (int hint);

        int getRenderType () const { return renderType; }
        m_ (setRenderType) void setRenderType (int t) { renderType = t; }

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
        int renderType; // TODO to powinno być typu Type
        Common::DataSource *dataSource;

        E_ (TTFFont)
};

} /* namespace View */

#endif /* TTFFONT_H_ */
#endif
