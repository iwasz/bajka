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

TTFFont::TTFFont (std::string const &path)
{
        open (path);
}

/****************************************************************************/

TTFFont::TTFFont (std::string const &path, int ptSize)
{
        open (path, ptSize);
}

/****************************************************************************/

TTFFont::TTFFont (std::string const &path, int ptSize, long int index)
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
                ptSize = 12;
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
        return renderSolid (text, fgColor);
}

/****************************************************************************/

void *TTFFont::renderSolid (std::string const &text, View::Color const &fgColor)
{
        SDL_Color fg = { fgColor.r * 255, fgColor.g * 255, fgColor.b * 255 };
        SDL_Surface *ret = TTF_RenderUTF8_Solid (font, text.c_str (), fg);

        if (!ret) {
                TTF_SetError("TTF rendering failed");
                throw Util::RuntimeException (TTF_GetError ());
        }

        return ret;
}

/****************************************************************************/

void *TTFFont::renderShaded (std::string const &text, View::Color const &fgColor, View::Color const &bgColor)
{

}

/****************************************************************************/

void *TTFFont::renderBlended (std::string const &text, View::Color const &fgColor)
{

}

} /* namespace View */
