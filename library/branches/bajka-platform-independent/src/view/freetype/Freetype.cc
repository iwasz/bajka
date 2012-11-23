/****************************************************************************
 *                                                                          *
 *  Author : based on SDL_ttf.                                              *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H
#include FT_GLYPH_H
#include FT_TRUETYPE_IDS_H

#include "Freetype.h"
#include "util/Exceptions.h"
#include "util/Math.h"
#include <memory>
#include <common/dataSource/DataSource.h>
#include <boost/make_shared.hpp>
#include "view/resource/IBitmap.h"
#include "view/resource/Bitmap.h"
#include "view/graphicFile/ColorSpace.h"
#include "view/draw/Color.h"
#include <vector>

/* FIXME: Right now we assume the gray-scale renderer Freetype is using
 supports 256 shades of gray, but we should instead key off of num_grays
 in the result FT_Bitmap after the FT_Render_Glyph() call. */
#define NUM_GRAYS       256

/* Handy routines for converting from fixed point */
#define FT_FLOOR(X)	((X & -64) / 64)
#define FT_CEIL(X)	(((X + 63) & -64) / 64)

#define CACHED_METRICS	0x10
#define CACHED_BITMAP	0x01
#define CACHED_PIXMAP	0x02

#define ALLOCA(n) malloc(n)
#define FREEA(p) free(p)

using namespace View;

/* Cached glyph information */
typedef struct cached_glyph {
        int stored;
        FT_UInt index;
        FT_Bitmap bitmap;
        FT_Bitmap pixmap;
        int minx;
        int maxx;
        int miny;
        int maxy;
        int yoffset;
        int advance;
        uint16_t cached;
} c_glyph;

/* The structure used to hold internal font information */
struct TTF_Font {

        ~TTF_Font ()
        {
                // TODO Czy to ma się tu kasować, czy nie!
                // delete src;
        }

        /* Freetype2 maintains all sorts of useful info itself */
        FT_Face face;

        /* We'll cache these ourselves */
        int height;
        int ascent;
        int descent;
        int lineskip;

        /* The font style */
        int face_style;
        int style;
        int outline;

        /* Whether kerning is desired */
        int kerning;

        /* Extra width in glyph bounds for text styles */
        int glyph_overhang;
        float glyph_italics;

        /* Information in the font for underlining */
        int underline_offset;
        int underline_height;

        /* Cache for style-transformed glyphs */
        c_glyph *current;
        c_glyph cache[257]; /* 257 is a prime */

        /* We are responsible for closing the font stream */
        Common::DataSource *src;
        int freesrc;
        FT_Open_Args args;

        /* For non-scalable formats, we must remember which font index size */
        int font_size_family;

        /* really just flags passed into FT_Load_Glyph */
        int hinting;
};

/* Handle a style only if the font does not already handle it */
#define TTF_HANDLE_STYLE_BOLD(font) (((font)->style & TTF_STYLE_BOLD) && \
                                    !((font)->face_style & TTF_STYLE_BOLD))
#define TTF_HANDLE_STYLE_ITALIC(font) (((font)->style & TTF_STYLE_ITALIC) && \
                                      !((font)->face_style & TTF_STYLE_ITALIC))

/* The FreeType font engine/library */
static FT_Library library;
static int TTF_initialized = 0;
static int TTF_byteswapped = 0;

typedef std::vector <uint16_t> UnicodeString;

/* Gets the top row of the underline. The outline
 is taken into account.
 */
static __inline__ int TTF_underline_top_row (TTF_Font *font)
{
        /* With outline, the underline_offset is underline_offset+outline. */
        /* So, we don't have to remove the top part of the outline height. */
        return font->ascent - font->underline_offset - 1;
}

/* Gets the top row of the underline. for a given glyph. The outline
 is taken into account.
 Need to update row according to height difference between font and glyph:
 font_value - font->ascent + glyph->maxy
 */
static __inline__ int TTF_Glyph_underline_top_row (TTF_Font *font, c_glyph *glyph)
{
        return glyph->maxy - font->underline_offset - 1;
}

/* Gets the bottom row of the underline. The outline
 is taken into account.
 */
static __inline__ int TTF_underline_bottom_row (TTF_Font *font)
{
        int row = TTF_underline_top_row (font) + font->underline_height;
        if (font->outline > 0) {
                /* Add underline_offset outline offset and */
                /* the bottom part of the outline. */
                row += font->outline * 2;
        }
        return row;
}

/* Gets the bottom row of the underline. for a given glyph. The outline
 is taken into account.
 Need to update row according to height difference between font and glyph:
 font_value - font->ascent + glyph->maxy
 */
static __inline__ int TTF_Glyph_underline_bottom_row (TTF_Font *font, c_glyph *glyph)
{
        return TTF_underline_bottom_row (font) - font->ascent + glyph->maxy;
}

/* Gets the top row of the strikethrough. The outline
 is taken into account.
 */
static __inline__ int TTF_strikethrough_top_row (TTF_Font *font)
{
        /* With outline, the first text row is 'outline'. */
        /* So, we don't have to remove the top part of the outline height. */
        return font->height / 2;
}

/* Gets the top row of the strikethrough for a given glyph. The outline
 is taken into account.
 Need to update row according to height difference between font and glyph:
 font_value - font->ascent + glyph->maxy
 */
static __inline__ int TTF_Glyph_strikethrough_top_row (TTF_Font *font, c_glyph *glyph)
{
        return TTF_strikethrough_top_row (font) - font->ascent + glyph->maxy;
}

/* This function tells the library whether UNICODE text is generally
 byteswapped.  A UNICODE BOM character at the beginning of a string
 will override this setting for that string.
 */
void TTF_ByteSwappedUNICODE (int swapped)
{
        TTF_byteswapped = swapped;
}

static void TTF_SetFTError (const char *msg, FT_Error error)
{
        throw Util::InitException (std::string ("Freetype : ") + msg);
}

int TTF_Init (void)
{
        int status = 0;

        if (!TTF_initialized) {
                FT_Error error = FT_Init_FreeType (&library);
                if (error) {
                        TTF_SetFTError ("Couldn't init FreeType engine", error);
                        status = -1;
                }
        }
        if (status == 0) {
                ++TTF_initialized;
        }
        return status;
}

/****************************************************************************/

static unsigned long RWread (FT_Stream stream, unsigned long offset, unsigned char* buffer, unsigned long count)
{
        Common::DataSource *src = (Common::DataSource *) stream->descriptor.pointer;
        src->seek ((int) offset, SEEK_SET);

        if (count == 0) {
                return 0;
        }

        return src->read (buffer, (int) count);
}

/****************************************************************************/

TTF_Font* TTF_OpenFontIndexRW (Common::DataSource *src, int freesrc, int ptsize, long index)
{
        TTF_Font* font;
        FT_Error error;
        FT_Face face;
        FT_Fixed scale;
        FT_Stream stream;
        FT_CharMap found;
        int position, i;

        if (!TTF_initialized) {
                throw Util::InitException ("Freetype : library not initialized");
        }

        /* Check to make sure we can seek in this stream */
        position = src->tell ();

        if (position < 0) {
                throw Util::InitException ("Freetype : can't seek in stream");
        }

        font = (TTF_Font*) malloc (sizeof *font);
        if (font == NULL) {
                throw Util::InitException ("Freetype : out of memory");
        }

        memset (font, 0, sizeof(*font));

        font->src = src;
        font->freesrc = freesrc;

        stream = (FT_Stream) malloc (sizeof(*stream));

        if (stream == NULL) {
                TTF_CloseFont (font);
                throw Util::InitException ("Freetype : Out of memory");
        }

        memset (stream, 0, sizeof(*stream));

        stream->read = RWread;
        stream->descriptor.pointer = src;
        stream->pos = (unsigned long) position;
        src->seek (0, SEEK_END);
        stream->size = (unsigned long) (src->tell () - position);
        src->seek (position, SEEK_SET);

        font->args.flags = FT_OPEN_STREAM;
        font->args.stream = stream;

        error = FT_Open_Face (library, &font->args, index, &font->face);
        if (error) {
                TTF_SetFTError ("Couldn't load font file", error);
                TTF_CloseFont (font);
                return NULL;
        }
        face = font->face;

        /* Set charmap for loaded font */
        found = 0;
        for (i = 0; i < face->num_charmaps; i++) {
                FT_CharMap charmap = face->charmaps[i];
                if ((charmap->platform_id == 3 && charmap->encoding_id == 1) /* Windows Unicode */
                || (charmap->platform_id == 3 && charmap->encoding_id == 0) /* Windows Symbol */
                || (charmap->platform_id == 2 && charmap->encoding_id == 1) /* ISO Unicode */
                || (charmap->platform_id == 0)) { /* Apple Unicode */
                        found = charmap;
                        break;
                }
        }
        if (found) {
                /* If this fails, continue using the default charmap */
                FT_Set_Charmap (face, found);
        }

        /* Make sure that our font face is scalable (global metrics) */
        if (FT_IS_SCALABLE (face)) {

                /* Set the character size and use default DPI (72) */
                error = FT_Set_Char_Size (font->face, 0, ptsize * 64, 0, 0);
                if (error) {
                        TTF_SetFTError ("Couldn't set font size", error);
                        TTF_CloseFont (font);
                        return NULL;
                }

                /* Get the scalable font metrics for this font */
                scale = face->size->metrics.y_scale;
                font->ascent = FT_CEIL(FT_MulFix(face->ascender, scale));
                font->descent = FT_CEIL(FT_MulFix(face->descender, scale));
                font->height = font->ascent - font->descent + /* baseline */1;
                font->lineskip = FT_CEIL(FT_MulFix(face->height, scale));
                font->underline_offset = FT_FLOOR(FT_MulFix(face->underline_position, scale));
                font->underline_height = FT_FLOOR(FT_MulFix(face->underline_thickness, scale));

        }
        else {
                /* Non-scalable font case.  ptsize determines which family
                 * or series of fonts to grab from the non-scalable format.
                 * It is not the point size of the font.
                 * */
                if (ptsize >= font->face->num_fixed_sizes)
                        ptsize = font->face->num_fixed_sizes - 1;
                font->font_size_family = ptsize;
                error = FT_Set_Pixel_Sizes (face, face->available_sizes[ptsize].height, face->available_sizes[ptsize].width);
                /* With non-scalale fonts, Freetype2 likes to fill many of the
                 * font metrics with the value of 0.  The size of the
                 * non-scalable fonts must be determined differently
                 * or sometimes cannot be determined.
                 * */
                font->ascent = face->available_sizes[ptsize].height;
                font->descent = 0;
                font->height = face->available_sizes[ptsize].height;
                font->lineskip = FT_CEIL(font->ascent);
                font->underline_offset = FT_FLOOR(face->underline_position);
                font->underline_height = FT_FLOOR(face->underline_thickness);
        }

        if (font->underline_height < 1) {
                font->underline_height = 1;
        }

#ifdef DEBUG_FONTS
        printf("Font metrics:\n");
        printf("\tascent = %d, descent = %d\n",
                        font->ascent, font->descent);
        printf("\theight = %d, lineskip = %d\n",
                        font->height, font->lineskip);
        printf("\tunderline_offset = %d, underline_height = %d\n",
                        font->underline_offset, font->underline_height);
        printf("\tunderline_top_row = %d, strikethrough_top_row = %d\n",
                        TTF_underline_top_row(font), TTF_strikethrough_top_row(font));
#endif

        /* Initialize the font face style */
        font->face_style = TTF_STYLE_NORMAL;
        if (font->face->style_flags & FT_STYLE_FLAG_BOLD) {
                font->face_style |= TTF_STYLE_BOLD;
        }
        if (font->face->style_flags & FT_STYLE_FLAG_ITALIC) {
                font->face_style |= TTF_STYLE_ITALIC;
        }
        /* Set the default font style */
        font->style = font->face_style;
        font->outline = 0;
        font->kerning = 1;
        font->glyph_overhang = face->size->metrics.y_ppem / 10;
        /* x offset = cos(((90.0-12)/360)*2*M_PI), or 12 degree angle */
        font->glyph_italics = 0.207f;
        font->glyph_italics *= font->height;

        return font;
}

TTF_Font* TTF_OpenFontRW (Common::DataSource *src, int freesrc, int ptsize)
{
        return TTF_OpenFontIndexRW (src, freesrc, ptsize, 0);
}

TTF_Font* TTF_OpenFontIndex (const char *file, int ptsize, long index)
{
        Common::DataSource *rw = new Common::DataSource;
        rw->open (file);
        return TTF_OpenFontIndexRW (rw, 1, ptsize, index);
}

TTF_Font* TTF_OpenFont (const char *file, int ptsize)
{
        return TTF_OpenFontIndex (file, ptsize, 0);
}

static void Flush_Glyph (c_glyph* glyph)
{
        glyph->stored = 0;
        glyph->index = 0;
        if (glyph->bitmap.buffer) {
                free (glyph->bitmap.buffer);
                glyph->bitmap.buffer = 0;
        }
        if (glyph->pixmap.buffer) {
                free (glyph->pixmap.buffer);
                glyph->pixmap.buffer = 0;
        }
        glyph->cached = 0;
}

static void Flush_Cache (TTF_Font* font)
{
        int i;
        int size = sizeof(font->cache) / sizeof(font->cache[0]);

        for (i = 0; i < size; ++i) {
                if (font->cache[i].cached) {
                        Flush_Glyph (&font->cache[i]);
                }

        }
}

static FT_Error Load_Glyph (TTF_Font* font, uint16_t ch, c_glyph* cached, int want)
{
        FT_Face face;
        FT_Error error;
        FT_GlyphSlot glyph;
        FT_Glyph_Metrics* metrics;
        FT_Outline* outline;

        if (!font || !font->face) {
                return FT_Err_Invalid_Handle;
        }

        face = font->face;

        /* Load the glyph */
        if (!cached->index) {
                cached->index = FT_Get_Char_Index (face, ch);
        }
        error = FT_Load_Glyph (face, cached->index, FT_LOAD_DEFAULT | font->hinting);
        if (error) {
                return error;
        }

        /* Get our glyph shortcuts */
        glyph = face->glyph;
        metrics = &glyph->metrics;
        outline = &glyph->outline;

        /**
         * Pobiera rozmiary glifu, jesli nie są one skeszowane w cached.
         */
        if ((want & CACHED_METRICS) && !(cached->stored & CACHED_METRICS)) {
                if (FT_IS_SCALABLE (face)) {
                        /* Get the bounding box */
                        cached->minx = FT_FLOOR(metrics->horiBearingX);
                        cached->maxx = cached->minx + FT_CEIL(metrics->width);
                        cached->maxy = FT_FLOOR(metrics->horiBearingY);
                        cached->miny = cached->maxy - FT_CEIL(metrics->height);
                        cached->yoffset = font->ascent - cached->maxy;
                        cached->advance = FT_CEIL(metrics->horiAdvance);
                }
                else {
                        /* Get the bounding box for non-scalable format.
                         * Again, freetype2 fills in many of the font metrics
                         * with the value of 0, so some of the values we
                         * need must be calculated differently with certain
                         * assumptions about non-scalable formats.
                         * */
                        cached->minx = FT_FLOOR(metrics->horiBearingX);
                        cached->maxx = cached->minx + FT_CEIL(metrics->horiAdvance);
                        cached->maxy = FT_FLOOR(metrics->horiBearingY);
                        cached->miny = cached->maxy - FT_CEIL(face->available_sizes[font->font_size_family].height);
                        cached->yoffset = 0;
                        cached->advance = FT_CEIL(metrics->horiAdvance);
                }

                /* Adjust for bold and italic text */
                if (TTF_HANDLE_STYLE_BOLD(font)) {
                        cached->maxx += font->glyph_overhang;
                }
                if (TTF_HANDLE_STYLE_ITALIC(font)) {
                        cached->maxx += (int) ceil (font->glyph_italics);
                }
                cached->stored |= CACHED_METRICS;
        }

        /**
         * Renderuje font, ale tylko jesli wynik renderowania nie jest skeszowany.
         */
        if (((want & CACHED_BITMAP) && !(cached->stored & CACHED_BITMAP)) || ((want & CACHED_PIXMAP) && !(cached->stored & CACHED_PIXMAP))) {
                int mono = (want & CACHED_BITMAP);
                int i;
                FT_Bitmap* src;
                FT_Bitmap* dst;
                FT_Glyph bitmap_glyph = NULL;

                /* Handle the italic style */
                if (TTF_HANDLE_STYLE_ITALIC(font)) {
                        FT_Matrix shear;

                        shear.xx = 1 << 16;
                        shear.xy = (int) (font->glyph_italics * (1 << 16)) / font->height;
                        shear.yx = 0;
                        shear.yy = 1 << 16;

                        FT_Outline_Transform (outline, &shear);
                }

                /* Render as outline */
                if ((font->outline > 0) && glyph->format != FT_GLYPH_FORMAT_BITMAP) {
                        FT_Stroker stroker;
                        FT_Get_Glyph (glyph, &bitmap_glyph);
                        error = FT_Stroker_New (library, &stroker);
                        if (error) {
                                return error;
                        }
                        FT_Stroker_Set (stroker, font->outline * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
                        FT_Glyph_Stroke (&bitmap_glyph, stroker, 1 /* delete the original glyph */);
                        FT_Stroker_Done (stroker);

                        /**
                         * Renderuje glif, który jest skalowalny, czyli zawiera outline (informację wektorową na temat
                         * fontu). Renderuje tylko do 2 formatów albo : FT_RENDER_MODE_MONO (1 bit per pixel ) lub
                         * FT_RENDER_MODE_NORMAL (odcienie szarości, ale nie wiadomo ile bitów - to zależy od fontu).
                         */
                        error = FT_Glyph_To_Bitmap (&bitmap_glyph, mono ? ft_render_mode_mono : ft_render_mode_normal, 0, 1);

                        if (error) {
                                FT_Done_Glyph (bitmap_glyph);
                                return error;
                        }

                        src = &((FT_BitmapGlyph) bitmap_glyph)->bitmap;
                }
                else {
                        /* Render the glyph */
                        error = FT_Render_Glyph (glyph, mono ? FT_RENDER_MODE_MONO : FT_RENDER_MODE_NORMAL);
                        if (error) {
                                return error;
                        }
                        src = &glyph->bitmap;
                }

                /**
                 * W zmiennej src jest dopiero co wyrenderowany glif. Kopiujemy go teraz do kesza. W keszu
                 * są dwie zmienne (bitmap i pixmap), uzywane w zależności od tego, czy mono, czy GRAY.
                 */
                if (mono) {
                        dst = &cached->bitmap;
                }
                else {
                        dst = &cached->pixmap;
                }

                /**
                 * Tu jest kopiowanie bajt po bajcie, ale oczywiście shallow, więc rózne inne bebechy też są
                 * kopiowane, ale niżej (między innymi oczywiście buffer, gdzie są dane obrazu).
                 */
                memcpy (dst, src, sizeof(*dst));

                /* FT_Render_Glyph() and .fon fonts always generate a
                 * two-color (black and white) glyphslot surface, even
                 * when rendered in ft_render_mode_normal. */
                /* FT_IS_SCALABLE() means that the font is in outline format,
                 * but does not imply that outline is rendered as 8-bit
                 * grayscale, because embedded bitmap/graymap is preferred
                 * (see FT_LOAD_DEFAULT section of FreeType2 API Reference).
                 * FT_Render_Glyph() canreturn two-color bitmap or 4/16/256-
                 * color graymap according to the format of embedded bitmap/
                 * graymap. */

                if (src->pixel_mode == FT_PIXEL_MODE_MONO) {
                        dst->pitch *= 8;
                }
                else if (src->pixel_mode == FT_PIXEL_MODE_GRAY2) {
                        dst->pitch *= 4;
                }
                else if (src->pixel_mode == FT_PIXEL_MODE_GRAY4) {
                        dst->pitch *= 2;
                }

                /* Adjust for bold and italic text */
                if (TTF_HANDLE_STYLE_BOLD(font)) {
                        int bump = font->glyph_overhang;
                        dst->pitch += bump;
                        dst->width += bump;
                }
                if (TTF_HANDLE_STYLE_ITALIC(font)) {
                        int bump = (int) ceil (font->glyph_italics);
                        dst->pitch += bump;
                        dst->width += bump;
                }

                /**
                 * Cały poniższy kod kopiuje bufor z src do dest. W buforze (pole buffer z FT_Bitmap) zawiera dane
                 * pixeli wyrenderowaego glifa. Formatów w src może być kilka (1, 2, 4 lub 8 bitów per pixel). Poniższy
                 * kod konwertuje te wszystkie formaty
                 */
                if (dst->rows != 0) {
                        dst->buffer = (unsigned char *) malloc (dst->pitch * dst->rows);

                        if (!dst->buffer) {
                                return FT_Err_Out_Of_Memory;
                        }

                        memset (dst->buffer, 0, dst->pitch * dst->rows);

                        for (i = 0; i < src->rows; i++) {
                                int soffset = i * src->pitch;
                                int doffset = i * dst->pitch;
                                if (mono) {
                                        unsigned char *srcp = src->buffer + soffset;
                                        unsigned char *dstp = dst->buffer + doffset;
                                        int j;
                                        if (src->pixel_mode == FT_PIXEL_MODE_MONO) {
                                                for (j = 0; j < src->width; j += 8) {
                                                        unsigned char c = *srcp++;
                                                        *dstp++ = (c & 0x80) >> 7;
                                                        c <<= 1;
                                                        *dstp++ = (c & 0x80) >> 7;
                                                        c <<= 1;
                                                        *dstp++ = (c & 0x80) >> 7;
                                                        c <<= 1;
                                                        *dstp++ = (c & 0x80) >> 7;
                                                        c <<= 1;
                                                        *dstp++ = (c & 0x80) >> 7;
                                                        c <<= 1;
                                                        *dstp++ = (c & 0x80) >> 7;
                                                        c <<= 1;
                                                        *dstp++ = (c & 0x80) >> 7;
                                                        c <<= 1;
                                                        *dstp++ = (c & 0x80) >> 7;
                                                }
                                        }
                                        else if (src->pixel_mode == FT_PIXEL_MODE_GRAY2) {
                                                for (j = 0; j < src->width; j += 4) {
                                                        unsigned char c = *srcp++;
                                                        *dstp++ = (((c & 0xA0) >> 6) >= 0x2) ? 1 : 0;
                                                        c <<= 2;
                                                        *dstp++ = (((c & 0xA0) >> 6) >= 0x2) ? 1 : 0;
                                                        c <<= 2;
                                                        *dstp++ = (((c & 0xA0) >> 6) >= 0x2) ? 1 : 0;
                                                        c <<= 2;
                                                        *dstp++ = (((c & 0xA0) >> 6) >= 0x2) ? 1 : 0;
                                                }
                                        }
                                        else if (src->pixel_mode == FT_PIXEL_MODE_GRAY4) {
                                                for (j = 0; j < src->width; j += 2) {
                                                        unsigned char c = *srcp++;
                                                        *dstp++ = (((c & 0xF0) >> 4) >= 0x8) ? 1 : 0;
                                                        c <<= 4;
                                                        *dstp++ = (((c & 0xF0) >> 4) >= 0x8) ? 1 : 0;
                                                }
                                        }
                                        else {
                                                for (j = 0; j < src->width; j++) {
                                                        unsigned char c = *srcp++;
                                                        *dstp++ = (c >= 0x80) ? 1 : 0;
                                                }
                                        }
                                }
                                else if (src->pixel_mode == FT_PIXEL_MODE_MONO) {
                                        /* This special case wouldn't
                                         * be here if the FT_Render_Glyph()
                                         * function wasn't buggy when it tried
                                         * to render a .fon font with 256
                                         * shades of gray.  Instead, it
                                         * returns a black and white surface
                                         * and we have to translate it back
                                         * to a 256 gray shaded surface.
                                         * */
                                        unsigned char *srcp = src->buffer + soffset;
                                        unsigned char *dstp = dst->buffer + doffset;
                                        unsigned char c;
                                        int j, k;
                                        for (j = 0; j < src->width; j += 8) {
                                                c = *srcp++;
                                                for (k = 0; k < 8; ++k) {
                                                        if ((c & 0x80) >> 7) {
                                                                *dstp++ = NUM_GRAYS - 1;
                                                        }
                                                        else {
                                                                *dstp++ = 0x00;
                                                        }
                                                        c <<= 1;
                                                }
                                        }
                                }
                                else if (src->pixel_mode == FT_PIXEL_MODE_GRAY2) {
                                        unsigned char *srcp = src->buffer + soffset;
                                        unsigned char *dstp = dst->buffer + doffset;
                                        unsigned char c;
                                        int j, k;
                                        for (j = 0; j < src->width; j += 4) {
                                                c = *srcp++;
                                                for (k = 0; k < 4; ++k) {
                                                        if ((c & 0xA0) >> 6) {
                                                                *dstp++ = NUM_GRAYS * ((c & 0xA0) >> 6) / 3 - 1;
                                                        }
                                                        else {
                                                                *dstp++ = 0x00;
                                                        }
                                                        c <<= 2;
                                                }
                                        }
                                }
                                else if (src->pixel_mode == FT_PIXEL_MODE_GRAY4) {
                                        unsigned char *srcp = src->buffer + soffset;
                                        unsigned char *dstp = dst->buffer + doffset;
                                        unsigned char c;
                                        int j, k;
                                        for (j = 0; j < src->width; j += 2) {
                                                c = *srcp++;
                                                for (k = 0; k < 2; ++k) {
                                                        if ((c & 0xF0) >> 4) {
                                                                *dstp++ = NUM_GRAYS * ((c & 0xF0) >> 4) / 15 - 1;
                                                        }
                                                        else {
                                                                *dstp++ = 0x00;
                                                        }
                                                        c <<= 4;
                                                }
                                        }
                                }
                                else {
                                        memcpy (dst->buffer + doffset, src->buffer + soffset, src->pitch);
                                }
                        }
                }

                /**
                 * W tym momencie w dst (czyli także w cached->pixmap lub jeśli mono == true, to w cached->bitmap)
                 * jest bitmapa 8 bit per pixel. Może być monochromatyczna, ale i tak zawsze jest 8 bitów na pixel.
                 * Ułatwia to późniejsze blitowanie.
                 */

                /* Handle the bold style */
                if (TTF_HANDLE_STYLE_BOLD(font)) {
                        int row;
                        int col;
                        int offset;
                        int pixel;
                        uint8_t* pixmap;

                        /* The pixmap is a little hard, we have to add and clamp */
                        for (row = dst->rows - 1; row >= 0; --row) {
                                pixmap = (uint8_t*) dst->buffer + row * dst->pitch;
                                for (offset = 1; offset <= font->glyph_overhang; ++offset) {
                                        for (col = dst->width - 1; col > 0; --col) {
                                                if (mono) {
                                                        pixmap[col] |= pixmap[col - 1];
                                                }
                                                else {
                                                        pixel = (pixmap[col] + pixmap[col - 1]);
                                                        if (pixel > NUM_GRAYS - 1) {
                                                                pixel = NUM_GRAYS - 1;
                                                        }
                                                        pixmap[col] = (uint8_t) pixel;
                                                }
                                        }
                                }
                        }
                }

                /* Mark that we rendered this format */
                if (mono) {
                        cached->stored |= CACHED_BITMAP;
                }
                else {
                        cached->stored |= CACHED_PIXMAP;
                }

                /* Free outlined glyph */
                if (bitmap_glyph) {
                        FT_Done_Glyph (bitmap_glyph);
                }
        }

        /* We're done, mark this glyph cached */
        cached->cached = ch;
        return 0;
}

static FT_Error Find_Glyph (TTF_Font* font, uint16_t ch, int want)
{
        int retval = 0;
        int hsize = sizeof(font->cache) / sizeof(font->cache[0]);

        int h = ch % hsize;
        font->current = &font->cache[h];

        if (font->current->cached != ch)
                Flush_Glyph (font->current);

        if ((font->current->stored & want) != want) {
                retval = Load_Glyph (font, ch, font->current, want);
        }
        return retval;
}

void TTF_CloseFont (TTF_Font* font)
{
        if (font) {
                Flush_Cache (font);
                if (font->face) {
                        FT_Done_Face (font->face);
                }
                if (font->args.stream) {
                        free (font->args.stream);
                }
                if (font->freesrc) {
                        font->src->close ();
                }
                free (font);
        }
}

static uint16_t *UTF8_to_UNICODE (uint16_t *unicode, const char *utf8, int len)
{
        int i, j;
        uint16_t ch;

        for (i = 0, j = 0; i < len; ++i, ++j) {
                ch = ((const unsigned char *) utf8)[i];
                if (ch >= 0xF0) {
                        ch = (uint16_t) (utf8[i] & 0x07) << 18;
                        ch |= (uint16_t) (utf8[++i] & 0x3F) << 12;
                        ch |= (uint16_t) (utf8[++i] & 0x3F) << 6;
                        ch |= (uint16_t) (utf8[++i] & 0x3F);
                }
                else if (ch >= 0xE0) {
                        ch = (uint16_t) (utf8[i] & 0x0F) << 12;
                        ch |= (uint16_t) (utf8[++i] & 0x3F) << 6;
                        ch |= (uint16_t) (utf8[++i] & 0x3F);
                }
                else if (ch >= 0xC0) {
                        ch = (uint16_t) (utf8[i] & 0x1F) << 6;
                        ch |= (uint16_t) (utf8[++i] & 0x3F);
                }
                unicode[j] = ch;
        }
        unicode[j] = 0;

        return unicode;
}

/**
 * Wynik trzeba zwolnić za pomocą delete [].
 */
std::auto_ptr <UnicodeString> utf8ToUnicode (const char *text)
{
        int unicode_len = strlen (text);
        std::auto_ptr <UnicodeString> unicode_text (new UnicodeString (unicode_len + 1));
        UTF8_to_UNICODE (&unicode_text->front (), text, unicode_len);
        return unicode_text;
}

int TTF_FontHeight (const TTF_Font *font)
{
        return (font->height);
}

int TTF_FontAscent (const TTF_Font *font)
{
        return (font->ascent);
}

int TTF_FontDescent (const TTF_Font *font)
{
        return (font->descent);
}

int TTF_FontLineSkip (const TTF_Font *font)
{
        return (font->lineskip);
}

int TTF_GetFontKerning (const TTF_Font *font)
{
        return (font->kerning);
}

void TTF_SetFontKerning (TTF_Font *font, int allowed)
{
        font->kerning = allowed;
}

long TTF_FontFaces (const TTF_Font *font)
{
        return (font->face->num_faces);
}

int TTF_FontFaceIsFixedWidth (const TTF_Font *font)
{
        return (FT_IS_FIXED_WIDTH (font->face));
}

char *TTF_FontFaceFamilyName (const TTF_Font *font)
{
        return (font->face->family_name);
}

char *TTF_FontFaceStyleName (const TTF_Font *font)
{
        return (font->face->style_name);
}

int TTF_GlyphIsProvided (const TTF_Font *font, uint16_t ch)
{
        return (FT_Get_Char_Index (font->face, ch));
}

int TTF_GlyphMetrics (TTF_Font *font, uint16_t ch, int* minx, int* maxx, int* miny, int* maxy, int* advance)
{
        FT_Error error;

        error = Find_Glyph (font, ch, CACHED_METRICS);
        if (error) {
                TTF_SetFTError ("Couldn't find glyph", error);
                return -1;
        }

        if (minx) {
                *minx = font->current->minx;
        }
        if (maxx) {
                *maxx = font->current->maxx;
                if (TTF_HANDLE_STYLE_BOLD(font)) {
                        *maxx += font->glyph_overhang;
                }
        }
        if (miny) {
                *miny = font->current->miny;
        }
        if (maxy) {
                *maxy = font->current->maxy;
        }
        if (advance) {
                *advance = font->current->advance;
                if (TTF_HANDLE_STYLE_BOLD(font)) {
                        *advance += font->glyph_overhang;
                }
        }
        return 0;
}

int TTF_SizeUNICODE (TTF_Font *font, uint16_t *text, int *w, int *h)
{
        int status;
        const uint16_t *ch;
        int x, z;
        int minx, maxx;
        int miny, maxy;
        c_glyph *glyph;
        FT_Error error;
        FT_Long use_kerning;
        FT_UInt prev_index = 0;
        int outline_delta = 0;

        /* Initialize everything to 0 */
        if (!TTF_initialized) {
                throw Util::InitException ("Freetype : Library not initialized");
        }
        status = 0;
        minx = maxx = 0;
        miny = maxy = 0;

        /* check kerning */
        use_kerning = FT_HAS_KERNING (font->face) && font->kerning;

        /* Init outline handling */
        if (font->outline > 0) {
                outline_delta = font->outline * 2;
        }

        /* Load each character and sum it's bounding box */
        x = 0;
        for (ch = text; *ch; ++ch) {
                uint16_t c = *ch;

                error = Find_Glyph (font, c, CACHED_METRICS);
                if (error) {
                        return -1;
                }
                glyph = font->current;

                /* handle kerning */
                if (use_kerning && prev_index && glyph->index) {
                        FT_Vector delta;
                        FT_Get_Kerning (font->face, prev_index, glyph->index, ft_kerning_default, &delta);
                        x += delta.x >> 6;
                }

#if 0
                if ( (ch == text) && (glyph->minx < 0) ) {
                        /* Fixes the texture wrapping bug when the first letter
                         * has a negative minx value or horibearing value.  The entire
                         * bounding box must be adjusted to be bigger so the entire
                         * letter can fit without any texture corruption or wrapping.
                         *
                         * Effects: First enlarges bounding box.
                         * Second, xstart has to start ahead of its normal spot in the
                         * negative direction of the negative minx value.
                         * (pushes everything to the right).
                         *
                         * This will make the memory copy of the glyph bitmap data
                         * work out correctly.
                         * */
                        z -= glyph->minx;

                }
#endif

                z = x + glyph->minx;
                if (minx > z) {
                        minx = z;
                }
                if (TTF_HANDLE_STYLE_BOLD(font)) {
                        x += font->glyph_overhang;
                }
                if (glyph->advance > glyph->maxx) {
                        z = x + glyph->advance;
                }
                else {
                        z = x + glyph->maxx;
                }
                if (maxx < z) {
                        maxx = z;
                }
                x += glyph->advance;

                if (glyph->miny < miny) {
                        miny = glyph->miny;
                }
                if (glyph->maxy > maxy) {
                        maxy = glyph->maxy;
                }
                prev_index = glyph->index;
        }

        /* Fill the bounds rectangle */
        if (w) {
                /* Add outline extra width */
                *w = (maxx - minx) + outline_delta;
        }
        if (h) {
                /* Some fonts descend below font height (FletcherGothicFLF) */
                /* Add outline extra height */
                *h = (font->ascent - miny) + outline_delta;
                if (*h < font->height) {
                        *h = font->height;
                }
        }
        return status;
}

int TTF_SizeUTF8 (TTF_Font *font, const char *inputText, int *w, int *h)
{
        std::auto_ptr <UnicodeString> textAuto = utf8ToUnicode (inputText);
        uint16_t *text = &textAuto->front ();
        return TTF_SizeUNICODE (font, text, w, h);
}

static inline uint8_t filterAllphaNoop (uint8_t a)
{
        return a;
}

static inline uint8_t filterAllphaMono (uint8_t a)
{
        return (a) ? 0xff : 0x00;
}

typedef uint8_t (*FilterAlphaFunctionPtr) (uint8_t a);

static Ptr <IBitmap> TTF_RenderUTF8_Impl (TTF_Font *font,
                                   const char *inputText,
                                   View::Color const &fg,
                                   int cacheType,
                                   FilterAlphaFunctionPtr fa,
                                   bool expandDimensions2)
{
        std::auto_ptr <UnicodeString> textAuto = utf8ToUnicode (inputText);
        uint16_t *text = &textAuto->front ();

        int width;
        int height;
        int visibleWidth;
        int visibleHeight;

        /* Get the dimensions of the text surface */
        if ((TTF_SizeUNICODE (font, text, &width, &height) < 0) || !width) {
                throw Util::InitException ("Freetype : Text has zero width");
        }

        Ptr <Bitmap> textBuf = boost::make_shared <Bitmap> ();
        visibleWidth = width;
        visibleHeight = height;

        if (expandDimensions2) {
                width = Util::Math::nextSqr (width);
                height = Util::Math::nextSqr (height);
        }

        textBuf->allocate (width, height, RGBA);
        textBuf->clear ();
        textBuf->setVisibleWidth (visibleWidth);
        textBuf->setVisibleHeight (visibleHeight);

        // Check kerning.
        FT_Long use_kerning = FT_HAS_KERNING (font->face) && font->kerning;

        /* Load and render each character */
        int xstart = 0;
        FT_UInt prev_index = 0;

        size_t textBufferPitch = textBuf->getPitch ();

        // Adding bound checking to avoid all kinds of memory corruption errors that may occur.
        uint8_t *lastByte = (uint8_t*) textBuf->getData () + textBuf->getPitch () * height;

        uint8_t r = fg.getR () * 255.0;
        uint8_t g = fg.getG () * 255.0;
        uint8_t b = fg.getB () * 255.0;
        uint8_t bytesPerColor = (textBuf->getColorSpace () == RGB) ? (3) : (4);

        for (const uint16_t *ch = text; *ch; ++ch) {
                uint16_t c = *ch;

                FT_Error error = Find_Glyph (font, c, CACHED_METRICS | cacheType);

                if (error) {
                        throw Util::InitException ("Freetype : Find_Glyph returned an error");
                }

                c_glyph *glyph = font->current;
                FT_Bitmap *current =  (cacheType == CACHED_BITMAP) ? (&glyph->bitmap) : (&glyph->pixmap);

                // Ensure the width of the pixmap is correct. On some cases, freetype may report a larger pixmap than possible.
                width = current->width;

                if (font->outline <= 0 && width > glyph->maxx - glyph->minx) {
                        width = glyph->maxx - glyph->minx;
                }

                // do kerning, if possible AC-Patch
                if (use_kerning && prev_index && glyph->index) {
                        FT_Vector delta;
                        FT_Get_Kerning (font->face, prev_index, glyph->index, ft_kerning_default, &delta);
                        xstart += delta.x >> 6;
                }

                /* Compensate for wrap around bug with negative minx's */
                if ((ch == text) && (glyph->minx < 0)) {
                        xstart -= glyph->minx;
                }

                /**
                 *  Tu jest kopiowanie do wyjściowej bitmapy. Iteruje po wierszach bitmapy.
                 */
                for (int row = 0; row < current->rows; ++row) {

                        // Make sure we don't go either over, or under the limit
                        if (row + glyph->yoffset < 0 || row + glyph->yoffset >= visibleHeight) {
                                continue;
                        }

                        // Początek aktualnej linijki o numerze row. Linia zawiera 8-bitowe odcienie szarości (może być mono).
                        uint8_t *src = current->buffer + row * current->pitch;

                        /*
                         * Tu kopiuje. SDL_ttf tworzy surface 8bitowe z paletą (?).
                         * row - wiersz numerowany od 0 (od góry do dołu?)
                         * glyph->yoffset - no to będzie jakieś przesuniecie wertykalne (przesunięcie do dołu).
                         * xstart - aktualna pozycja pióra X - powiększana po narysowaniu glifu o jego szerokość (xstart += glyph->advance;).
                         * glyph->minx - margines glifu.
                         */
                        uint8_t *dst = (uint8_t*) textBuf->getData () + (row + glyph->yoffset) * textBufferPitch + (xstart + glyph->minx) * bytesPerColor;

                        // Kopiowaine pojedynczego wiersza.
                        for (int col = 0; col < width && dst < lastByte; ++col) {
                                *dst++ = r;
                                *dst++ = g;
                                *dst++ = b;
                                *dst++ = (*fa) (*src++);
                        }
                }

                xstart += glyph->advance;

                if (TTF_HANDLE_STYLE_BOLD (font)) {
                        xstart += font->glyph_overhang;
                }

                prev_index = glyph->index;
        }

        return textBuf;
}

Ptr <IBitmap> TTF_RenderUTF8_Solid (TTF_Font *font, const char *inputText, View::Color const &fg, bool expandDimensions2)
{
        return TTF_RenderUTF8_Impl (font, inputText, fg, CACHED_BITMAP, filterAllphaMono, expandDimensions2);
}

Ptr <IBitmap> TTF_RenderUTF8_Blended (TTF_Font *font, const char *inputText, View::Color const &fg, bool expandDimensions2)
{
        return TTF_RenderUTF8_Impl (font, inputText, fg, CACHED_PIXMAP, filterAllphaNoop, expandDimensions2);
}


void TTF_SetFontStyle (TTF_Font* font, int style)
{
        font->style = style | font->face_style;
}

int TTF_GetFontStyle (const TTF_Font* font)
{
        return font->style;
}

void TTF_SetFontOutline (TTF_Font* font, int outline)
{
        font->outline = outline;
        Flush_Cache (font);
}

int TTF_GetFontOutline (const TTF_Font* font)
{
        return font->outline;
}

void TTF_SetFontHinting (TTF_Font* font, int hinting)
{
        if (hinting == TTF_HINTING_LIGHT)
                font->hinting = FT_LOAD_TARGET_LIGHT;
        else if (hinting == TTF_HINTING_MONO)
                font->hinting = FT_LOAD_TARGET_MONO;
        else if (hinting == TTF_HINTING_NONE)
                font->hinting = FT_LOAD_NO_HINTING;
        else
                font->hinting = 0;

        Flush_Cache (font);
}

int TTF_GetFontHinting (const TTF_Font* font)
{
        if (font->hinting == FT_LOAD_TARGET_LIGHT)
                return TTF_HINTING_LIGHT;
        else if (font->hinting == FT_LOAD_TARGET_MONO)
                return TTF_HINTING_MONO;
        else if (font->hinting == FT_LOAD_NO_HINTING)
                return TTF_HINTING_NONE;
        return 0;
}

void TTF_Quit (void)
{
        if (TTF_initialized) {
                if (--TTF_initialized == 0) {
                        FT_Done_FreeType (library);
                }
        }
}

int TTF_WasInit (void)
{
        return TTF_initialized;
}

int TTF_GetFontKerningSize (TTF_Font* font, int prev_index, int index)
{
        FT_Vector delta;
        FT_Get_Kerning (font->face, prev_index, index, ft_kerning_default, &delta);
        return (delta.x >> 6);
}
