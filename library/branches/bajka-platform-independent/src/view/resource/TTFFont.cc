/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#if 0
#ifdef USE_SDL
#include <boost/algorithm/string.hpp>
#include <SDL/SDL_ttf.h>
#include "TTFFont.h"
#include "util/Exceptions.h"
#include "Bitmap.h"

namespace View {

TTFFont::TTFFont (std::string const &path) : type (SOLID), utf8 (false)
{
        open (path);
}

/****************************************************************************/

TTFFont::TTFFont (std::string const &path, int ptSize) : type (SOLID), utf8 (false)
{
        open (path, ptSize);
}

/****************************************************************************/

TTFFont::TTFFont (std::string const &path, int ptSize, long int index) : type (SOLID), utf8 (false)
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

Ptr <IBitmap> TTFFont::render (std::string const &text, View::Color const &fgColor, View::Color const &bgColor)
{
        SDL_Color fg = { fgColor.r * 255, fgColor.g * 255, fgColor.b * 255 };
        SDL_Surface *ret = NULL;

        switch (type) {
        case SOLID:
                ret = (utf8) ? (TTF_RenderUTF8_Solid (font, text.c_str (), fg)) : (TTF_RenderText_Solid (font, text.c_str (), fg));
                break;

        case SHADED:
        {
                SDL_Color bg = { bgColor.r * 255, bgColor.g * 255, bgColor.b * 255 };
                ret = (utf8) ? (TTF_RenderUTF8_Shaded (font, text.c_str (), fg, bg)) : (TTF_RenderText_Shaded (font, text.c_str (), fg, bg));
                break;
        }

        case BLENDED:
                ret = (utf8) ? (TTF_RenderUTF8_Blended (font, text.c_str (), fg)) : (TTF_RenderText_Blended (font, text.c_str (), fg));
                break;
        }


        if (!ret) {
                TTF_SetError("TTF rendering failed");
                throw Util::RuntimeException (TTF_GetError ());
        }

        Uint32 saved_flags = ret->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);

        if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) {
                SDL_SetAlpha (ret, 0, 0);
        }

        return boost::make_shared <Bitmap> (ret);
}

/****************************************************************************/

Ptr <IBitmap> TTFFont::renderMulti (std::string const &text, View::Color const &fgColor, View::Color const &bgColor, TextAlign textLaign)
{
        // Bez lineWrapu.
        int lineSkip = TTF_FontLineSkip (font);
        int width = 0, height = 0;

        Core::StringVector tokens;
        boost::algorithm::split (tokens, text, boost::algorithm::is_any_of ("\n"));

        // Ustal jaka będzie szerokość w pixelach najdłuższej wyrenderowanej linijki.
        for (Core::StringVector::const_iterator i = tokens.begin (); i != tokens.end (); ++i) {
                int w = 0;

                if (utf8) {
                        TTF_SizeUTF8 (font, i->c_str (), &w, &height);
                }
                else {
                        TTF_SizeText (font, i->c_str (), &w, &height);
                }

                if (w > width) {
                        width = w;
                }
        }

        // Jaka będzie wysokość bloku tekstu (wszystkich wyrenderowanych linijek
        height = (tokens.size () - 1) * lineSkip + height;

        // Stwórz surface zdolne pomiescić cały tekst (wszytskie linijki).
        SDL_Surface *surface = GraphicsService::createSurface (width, height);

        // Renderuj
        int cnt = 0;

        for (Core::StringVector::const_iterator i = tokens.begin (); i != tokens.end (); ++i, ++cnt) {

                if (i->empty ()) {
                        continue;
                }

                // The rendered text:
                Ptr <IBitmap> sTemp = render (*i, fgColor, bgColor);

                // Put it on the surface (sText):
                SDL_Rect destRct = { 0, cnt * lineSkip, 0, 0 };

                if (textLaign == CENTER) {
                        destRct.x = (surface->w - sTemp->getWidth ()) / 2;
                }
                else if (textLaign == RIGHT) {
                        destRct.x = (surface->w - sTemp->getWidth ());
                }

                // Niemożliwe, żeby nie przeszło, ale i tak...
                assertThrow (destRct.x >= 0, "TTFFont::renderMulti : destRct.x < 0")

//                TODO
//                SDL_BlitSurface (sTemp->getData (), NULL, surface, &destRct);

                // Clean up:
                //SDL_FreeSurface(sTemp);
        }

        return boost::make_shared <Bitmap> (surface);
}

/****************************************************************************/

int TTFFont::getHinting () const
{
        return TTF_GetFontHinting (font);
}

/****************************************************************************/

void TTFFont::setHinting (int hint)
{
        if (TTF_GetFontHinting (font) == hint) {
                return;
        }

        TTF_SetFontHinting (font, hint);
}

/****************************************************************************/

int TTFFont::getStyle () const
{
        return TTF_GetFontStyle (font);
}

/****************************************************************************/

void TTFFont::setStyle (int i)
{
        if (TTF_GetFontStyle (font) == i) {
                return;
        }

        TTF_SetFontStyle (font, i);
}

/****************************************************************************/

int TTFFont::getOutline () const
{
        return TTF_GetFontOutline (font);
}

/****************************************************************************/

void TTFFont::setOutline (int i)
{
        TTF_SetFontOutline (font, i);
}

/****************************************************************************/

bool TTFFont::getKerning () const
{
        return TTF_GetFontKerning (font);
}

/****************************************************************************/

void TTFFont::setKerning (bool b)
{
        TTF_SetFontKerning (font, b);
}

} /* namespace View */
#endif
#endif
