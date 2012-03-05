/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_ttf.h>
#include "TTFFont.h"
#include "../../util/Exceptions.h"

namespace View {

TTFFont::TTFFont (std::string const &path) : type (SOLID), encoding (ASCII)
{
        open (path);
}

/****************************************************************************/

TTFFont::TTFFont (std::string const &path, int ptSize) : type (SOLID), encoding (ASCII)
{
        open (path, ptSize);
}

/****************************************************************************/

TTFFont::TTFFont (std::string const &path, int ptSize, long int index) : type (SOLID), encoding (ASCII)
{
        open (path, ptSize, index);
}

/****************************************************************************/

TTFFont::~TTFFont ()
{
        TTF_CloseFont (font);
}

/****************************************************************************/

void TTFFont::open (std::string const &path, int ptSize, long int index)
{
        if (ptSize < 0) {
                ptSize = 36;
        }

        if (index < 0) {
                index = 0;
        }

        font = TTF_OpenFontIndex (path.c_str (), ptSize, index);

        if (!font) {
                throw Util::InitException (TTF_GetError ());
        }
}

/****************************************************************************/

void *TTFFont::render (std::string const &text, View::Color const &fgColor, View::Color const &bgColor)
{
        SDL_Color fg = { fgColor.r * 255, fgColor.g * 255, fgColor.b * 255 };
        SDL_Surface *ret;

        switch (type) {
        case SOLID:
                if (encoding == UTF8) {
                        ret = TTF_RenderUTF8_Solid (font, text.c_str (), fg);
                }
                else {
                        ret = TTF_RenderText_Solid (font, text.c_str (), fg);
                }
                break;

        case SHADED:
        {
                SDL_Color bg = { bgColor.r * 255, bgColor.g * 255, bgColor.b * 255 };
                if (encoding == UTF8) {
                        ret = TTF_RenderUTF8_Shaded (font, text.c_str (), fg, bg);
                }
                else {
                        ret = TTF_RenderText_Shaded (font, text.c_str (), fg, bg);
                }
                break;
        }

        case BLENDED:
                if (encoding == UTF8) {
                        ret = TTF_RenderUTF8_Blended (font, text.c_str (), fg);
                }
                else {
                        ret = TTF_RenderText_Blended (font, text.c_str (), fg);
                }
                break;
        }


        if (!ret) {
                TTF_SetError("TTF rendering failed");
                throw Util::RuntimeException (TTF_GetError ());
        }

        return ret;
}

/****************************************************************************/

int TTFFont::getHinting () const
{
//        return TTF_GetFontHinting (font);
        return 0;
}

/****************************************************************************/

void TTFFont::setHinting (int hint)
{
//        if (TTF_GetFontHinting (font) == hint) {
//                return;
//        }
//
//        TTF_SetFontHinting (font, hint);
}

} /* namespace View */
