/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <zlib.h>
#include <png.h>
#include <string>
#include <iostream>
#include "Png.h"
#include "util/Exceptions.h"
#include <cstdlib>
#include "util/Math.h"

namespace View {

/****************************************************************************/

#define PNG_BYTES_TO_CHECK 8
static void pngtestWarning (png_structp png_ptr, png_const_charp message);
static void pngtestError (png_structp png_ptr, png_const_charp message);

/****************************************************************************/

void pngLoad (void *source,
              void **data,
              int *widthOut,
              int *heightOut,
              int *visibleWidthOut,
              int *visibleHeightOut,
              ColorSpace *colorSpace,
              int *bitDepth,
              bool expandDimensions2)
{
        png_structp png_ptr;
        png_infop info_ptr;
        png_uint_32 width, height;
        int bit_depth, color_type, interlace_type;
        FILE *fp = static_cast <FILE *> (source);

        /*
         * Create and initialize the png_struct with the desired error handler
         * functions.  If you want to use the default stderr and longjump method,
         * you can supply NULL for the last three parameters.  We also supply the
         * the compiler header file version, so that we know if the application
         * was compiled with a compatible version of the library.  REQUIRED
         */
        std::string errorStringFromHandler;
        png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, (png_voidp)&errorStringFromHandler, pngtestError, pngtestWarning);

        if (png_ptr == NULL) {
                fclose(fp);
                throw Util::InitException ("pngLoad : error creating png_struct with png_create_read_struct");
        }

        /* Allocate/initialize the memory for image information.  REQUIRED. */
        info_ptr = png_create_info_struct (png_ptr);

        if (info_ptr == NULL) {
                fclose(fp);
                png_destroy_read_struct(&png_ptr, NULL, NULL);
                throw Util::InitException ("pngLoad : error creating png_info with png_create_info_struct");
        }

        if (setjmp (png_jmpbuf (png_ptr))) {
                /* Free all of the memory associated with the png_ptr and info_ptr */
                png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
                fclose(fp);

                /* If we get here, we had a problem reading the file */
                throw Util::InitException("pngLoad : an error occured : " + errorStringFromHandler);
        }

        /* Set up the input control if you are using standard C streams */
        png_init_io (png_ptr, fp);

        /* Read PNG header info */
        png_read_info (png_ptr, info_ptr);
        png_get_IHDR (png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);

        /* tell libpng to strip 16 bit/color files down to 8 bits/color */
        png_set_strip_16 (png_ptr);

        /* Extract multiple pixels with bit depths of 1, 2, and 4 from a single
         * byte into separate bytes (useful for paletted and grayscale images).
         */
        png_set_packing (png_ptr);

        if (color_type == PNG_COLOR_TYPE_PALETTE) {
            png_set_palette_to_rgb (png_ptr);
        }

        if (png_get_valid (png_ptr, info_ptr, PNG_INFO_tRNS)) {
                png_set_tRNS_to_alpha (png_ptr);
        }

        if ((color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) && bit_depth < 8) {
                png_set_expand_gray_1_2_4_to_8(png_ptr);
        }

        if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
                png_set_gray_to_rgb (png_ptr);
        }

        // Dodaje kanał alpha - możliwe, że nadmiarowo, ale chcę mieć RGBA 8888
        png_set_add_alpha (png_ptr, 0xff, PNG_FILLER_AFTER);

        // Tu mamy pewność, że format odczytanych danych to będzie RGBA 8888

        png_read_update_info (png_ptr, info_ptr);
        png_get_IHDR (png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);
        int num_channels = png_get_channels(png_ptr, info_ptr);

        if (expandDimensions2) {
                *widthOut = Util::Math::nextSqr (width);
                *heightOut = Util::Math::nextSqr (height);
        }
        else {
                *widthOut = width;
                *heightOut = height;
        }

        *visibleWidthOut = width;
        *visibleHeightOut = height;
        *colorSpace = RGBA;
        *bitDepth = bit_depth;

        *data = malloc (*widthOut * *heightOut * (bit_depth / 8) * num_channels);

        if (!data) {
                throw Util::InitException("pngLoad : out of memory");
        }

        /* Create the array of pointers to image data */
        png_bytep *row_pointers = (png_bytep*) malloc (sizeof(png_bytep) * height);

        if (!row_pointers) {
                throw Util::InitException("pngLoad : out of memory");
        }

        int scanLineLen = *widthOut * (bit_depth / 8) * num_channels;
        int shiftYBytes = (*heightOut - height) * scanLineLen;

        for (int row = 0; row < (int)height; ++row) {
                row_pointers[row] = (png_bytep)*data + row * scanLineLen /*+ shiftXBytes*/ + shiftYBytes;
        }

        /* Read the entire image in one go */
        png_read_image (png_ptr, row_pointers);

        free (row_pointers);

        /* Clean up after the read, and free any memory allocated - REQUIRED */
        png_destroy_read_struct (&png_ptr, &info_ptr, NULL);

        /* Close the file */
        fclose(fp);

#if 0
        std::cerr << "w = " << *widthOut << ", h = " << *heightOut << ", bits = " << bit_depth << ", chan = " << num_channels << ", shiftXBytes = " << shiftXBytes << std::endl;
#endif
}

/****************************************************************************/

bool checkIfPng (void *source)
{
        unsigned char buf[PNG_BYTES_TO_CHECK];

        /* Open the prospective PNG file. */
        FILE *fp = static_cast <FILE *> (source);

        /* Read in some of the signature bytes */
        if (fread (buf, 1, PNG_BYTES_TO_CHECK, fp) != PNG_BYTES_TO_CHECK)
                return false;

        /* Compare the first PNG_BYTES_TO_CHECK bytes of the signature.
         Return nonzero (true) if they match */
        return (!png_sig_cmp (buf, (png_size_t) 0, PNG_BYTES_TO_CHECK));
}

/* This function is called when there is a warning, but the library thinks
 * it can continue anyway.  Replacement functions don't have to do anything
 * here if you don't want to.  In the default configuration, png_ptr is
 * not used, but it is passed in case it may be useful.
 */
static void pngtestWarning (png_structp png_ptr, png_const_charp message)
{
        std::cerr << "libpng warning:" << message << std::endl;
}

/* This is the default error handling function.  Note that replacements for
 * this function MUST NOT RETURN, or the program will likely crash.  This
 * function is used by default, or if the program supplies NULL for the
 * error function pointer in png_set_error_fn().
 */
static void pngtestError(png_structp png_ptr, png_const_charp message)
{
        std::string *userObject = static_cast <std::string *> (png_get_error_ptr (png_ptr));
        *userObject = std::string ("Fatal libpng error : ") + message;
}

} // namespace
