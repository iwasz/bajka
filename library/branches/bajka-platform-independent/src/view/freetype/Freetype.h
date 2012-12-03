/****************************************************************************
 *                                                                          *
 *  Author : based on SDL_ttf.                                              *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_FREETYPE_TTF_H
#define BAJKA_FREETYPE_TTF_H

#include <stdint.h>
#include <common/dataSource/DataSource.h>
#include <core/Pointer.h>

namespace View {
class Color;
class IBitmap;
}

/* The internal structure containing font information */
struct TTF_Font;

/* Initialize the TTF engine - returns 0 if successful, -1 on error */
extern int ttfInit (void);

/* Open a font file and create a font of the specified point size.
 * Some .fon fonts will have several sizes embedded in the file, so the
 * point size becomes the index of choosing which size.  If the value
 * is too high, the last indexed size will be the default. */
extern TTF_Font * ttfOpenFont (const char *file, int ptsize);
extern TTF_Font * ttfOpenFont (const char *file, int ptsize, long index);
extern TTF_Font * ttfOpenFont (Common::DataSource *src, const char *file, int freesrc, int ptsize);
extern TTF_Font * ttfOpenFont (Common::DataSource *src, const char *file, int freesrc, int ptsize, long index);

/* Set and retrieve the font style */
#define TTF_STYLE_NORMAL	0x00
#define TTF_STYLE_BOLD		0x01
#define TTF_STYLE_ITALIC	0x02

extern int ttfGetFontStyle (const TTF_Font *font);
extern void ttfSetFontStyle (TTF_Font *font, int style);
extern int ttfGetFontOutline (const TTF_Font *font);
extern void ttfSetFontOutline (TTF_Font *font, int outline);

/* Set and retrieve FreeType hinter settings */
#define TTF_HINTING_NORMAL    0
#define TTF_HINTING_LIGHT     1
#define TTF_HINTING_MONO      2
#define TTF_HINTING_NONE      3

extern int ttfGetFontHinting (const TTF_Font *font);
extern void ttfSetFontHinting (TTF_Font *font, int hinting);

/* Get the total height of the font - usually equal to point size */
extern int ttfFontHeight (const TTF_Font *font);

/* Get the offset from the baseline to the top of the font
 This is a positive value, relative to the baseline.
 */
extern int ttfFontAscent (const TTF_Font *font);

/* Get the offset from the baseline to the bottom of the font
 This is a negative value, relative to the baseline.
 */
extern int ttfFontDescent (const TTF_Font *font);

/* Get the recommended spacing between lines of text for this font */
extern int ttfFontLineSkip (const TTF_Font *font);

/* Get/Set whether or not kerning is allowed for this font */
extern int ttfGetFontKerning (const TTF_Font *font);
extern void ttfSetFontKerning (TTF_Font *font, int allowed);

/* Get the number of faces of the font */
extern long ttfFontFaces (const TTF_Font *font);

/* Get the font face attributes, if any */
extern int ttfFontFaceIsFixedWidth (const TTF_Font *font);
extern char * ttfFontFaceFamilyName (const TTF_Font *font);
extern char * ttfFontFaceStyleName (const TTF_Font *font);

/* Check wether a glyph is provided by the font or not */
extern int ttfGlyphIsProvided (const TTF_Font *font, uint16_t ch);

/* Get the metrics (dimensions) of a glyph
 To understand what these metrics mean, here is a useful link:
 http://freetype.sourceforge.net/freetype2/docs/tutorial/step2.html
 */
extern int ttfGlyphMetrics (TTF_Font *font, uint16_t ch, int *minx, int *maxx, int *miny, int *maxy, int *advance);

/* Get the dimensions of a rendered string of text */
extern int ttfSizeUTF8 (TTF_Font *font, const char *text, int *w, int *h);

/* Close an opened font file */
extern void ttfCloseFont (TTF_Font *font);

/* De-initialize the TTF engine */
extern void ttfQuit (void);

/* Check if the TTF engine is initialized */
extern int ttfWasInit (void);

/* Get the kerning size of two glyphs */
extern int ttfGetFontKerningSize (TTF_Font *font, int prev_index, int index);

/* Create an 8-bit palettized surface and render the given text at
 fast quality with the given font and color.  The 0 pixel is the
 colorkey, giving a transparent background, and the 1 pixel is set
 to the text color.
 This function returns the new surface, or NULL if there was an error.
 */
extern Ptr <View::IBitmap> ttfRenderUTF8Solid (TTF_Font *font, const char *text, View::Color const &, bool expandDimensions2 = true);


/* Create a 32-bit ARGB surface and render the given text at high quality,
 using alpha blending to dither the font with the given color.
 This function returns the new surface, or NULL if there was an error.
 */
extern Ptr <View::IBitmap> ttfRenderUTF8Blended (TTF_Font *font, const char *text, View::Color const &, bool expandDimensions2 = true);


#endif /* _SDL_TTF_H */
