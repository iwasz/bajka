/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/algorithm/string.hpp>
#include "TTFFont.h"
#include "view/freetype/Freetype.h"
#include "util/Exceptions.h"
#include "view/resource/Bitmap.h"
#include "Platform.h"
#include <common/dataSource/DataSource.h>

namespace View {

TTFFont::TTFFont (std::string const &path) : renderType (SOLID), dataSource (NULL)
{
        open (path);
}

/****************************************************************************/

TTFFont::TTFFont (std::string const &path, int ptSize) : renderType (SOLID), dataSource (NULL)
{
        open (path, ptSize);
}

/****************************************************************************/

TTFFont::TTFFont (std::string const &path, int ptSize, long int index) : renderType (SOLID), dataSource (NULL)
{
        open (path, ptSize, index);
}

/****************************************************************************/

TTFFont::~TTFFont ()
{
        ttfCloseFont (font);
        deleteDataSource (dataSource);
        font = NULL;
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


        deleteDataSource (dataSource);
        dataSource = newDataSource ();

        font = ttfOpenFont (dataSource, path.c_str (), ptSize, index);

        if (!font) {
                throw Util::InitException ("TTFFont::open : !font");
        }
}

/****************************************************************************/

Ptr <IBitmap> TTFFont::render (std::string const &text, View::Color const &fgColor)
{
        switch (renderType) {
        case SOLID:
                return ttfRenderUTF8Solid (font, text.c_str (), fgColor, true);

        case BLENDED:
                return ttfRenderUTF8Blended (font, text.c_str (), fgColor, true);
        }

        throw Util::RuntimeException ("TTFFont::render : unknown renderType");
}

/****************************************************************************/

Ptr <IBitmap> TTFFont::renderMulti (std::string const &text, View::Color const &fgColor, TextAlign textLaign)
{
#if 0
//        TODO
        // Bez lineWrapu.
        int lineSkip = ttfFontLineSkip (font);
        int width = 0, height = 0;

        Core::StringVector tokens;
        boost::algorithm::split (tokens, text, boost::algorithm::is_any_of ("\n"));

        // Ustal jaka będzie szerokość w pixelach najdłuższej wyrenderowanej linijki.
        for (Core::StringVector::const_iterator i = tokens.begin (); i != tokens.end (); ++i) {
                int w = 0;
                ttfSizeUTF8 (font, i->c_str (), &w, &height);

                if (w > width) {
                        width = w;
                }
        }

        // Jaka będzie wysokość bloku tekstu (wszystkich wyrenderowanych linijek
        height = (tokens.size () - 1) * lineSkip + height;

        // Stwórz surface zdolne pomiescić cały tekst (wszytskie linijki).
        SDL_Surface *surface = createSurface (width, height);

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
#endif
        return boost::make_shared <Bitmap> (/*surface*/);
}

/****************************************************************************/

int TTFFont::getHinting () const
{
        return ttfGetFontHinting (font);
}

/****************************************************************************/

void TTFFont::setHinting (int hint)
{
        if (ttfGetFontHinting (font) == hint) {
                return;
        }

        ttfSetFontHinting (font, hint);
}

/****************************************************************************/

int TTFFont::getStyle () const
{
        return ttfGetFontStyle (font);
}

/****************************************************************************/

void TTFFont::setStyle (int i)
{
        if (ttfGetFontStyle (font) == i) {
                return;
        }

        ttfSetFontStyle (font, i);
}

/****************************************************************************/

int TTFFont::getOutline () const
{
        return ttfGetFontOutline (font);
}

/****************************************************************************/

void TTFFont::setOutline (int i)
{
        ttfSetFontOutline (font, i);
}

/****************************************************************************/

bool TTFFont::getKerning () const
{
        return ttfGetFontKerning (font);
}

/****************************************************************************/

void TTFFont::setKerning (bool b)
{
        ttfSetFontKerning (font, b);
}

} /* namespace View */
