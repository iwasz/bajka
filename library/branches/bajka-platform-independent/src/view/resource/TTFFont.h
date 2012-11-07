///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#ifndef BAJKA_TTFFONT_H_
//#define BAJKA_TTFFONT_H_
//
//#include "util/ReflectionMacros.h"
//#include "view/resource/IFont.h"
//
//struct _TTF_Font;
//typedef struct _TTF_Font TTF_Font;
//
//namespace View {
//
//class TTFFont : public IFont {
//public:
//
//        C__ (std::string const &)
//        TTFFont (std::string const &path);
//
//        C_ (std::string const &, int)
//        TTFFont (std::string const &path, int ptSize);
//
//        C_ (std::string const &, int, long int)
//        TTFFont (std::string const &path, int ptSize, long int index);
//
//        ~TTFFont ();
//
//        enum Type {
//                SOLID,
//                SHADED,
//                BLENDED
//        };
//
//        // TODO To jest skopiowane z SDL/SDL_ttf, żeby nie inkludowac nagłówków z SDL. Dzięki temu program klienta nie musi miec zależności do SDL.
//        enum Style {
//                NORMAL          = 0x00,
//                BOLD            = 0x01,
//                ITALIC          = 0x02,
//                UNDERLINE       = 0x04,
//                STRIKETHROUGH   = 0x08
//        };
//
//        // TODO Tu jest jakoś źle chyba.
//        enum Hinting {
//                FULL,
//                LIGHT,
//                MONO,
//                NONE
//        };
//
//        Ptr <IBitmap> render (std::string const &text, View::Color const &fgColor, View::Color const &bgColor);
//        Ptr <IBitmap> renderMulti (std::string const &text, View::Color const &fgColor, View::Color const &bgColor, TextAlign textAlign = LEFT);
//
//        // TODO Typ zwracany powinien być Hinting
//        int getHinting () const;
//        m_ (setHinting) void setHinting (int hint);
//
//        int getRenderType () const { return renderType; }
//        m_ (setRenderType) void setRenderType (int t) { renderType = t; }
//
//        bool getUtf8 () const { return utf8; }
//        m_ (setUtf8) void setUtf8 (bool b) { utf8 = b; }
//
//        int getStyle () const;
//        m_ (setStyle) void setStyle (int i);
//
//        int getOutline () const;
//        m_ (setOutline) void setOutline (int i);
//
//        bool getKerning () const;
//        m_ (setKerning) void setKerning (bool b);
//
//private:
//
//        void open (std::string const &path, int ptSize = -1, long int index = -1);
//
//private:
//
//        TTF_Font *font;
//        int renderType; // TODO to powinno być typu Type
//        bool utf8;
//
//        E_ (TTFFont)
//};
//
//} /* namespace View */
//
//#endif /* TTFFONT_H_ */
