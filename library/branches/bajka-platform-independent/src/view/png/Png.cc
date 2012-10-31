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

/****************************************************************************/

#define PNG_BYTES_TO_CHECK 8
static void pngtestWarning (png_structp png_ptr, png_const_charp message);
static void pngtestError (png_structp png_ptr, png_const_charp message);

/****************************************************************************/

void pngLoad (const char *path)
{
        png_structp png_ptr;
        png_infop info_ptr;
        unsigned int sig_read = 0;
        png_uint_32 width, height;
        int bit_depth, color_type, interlace_type;
        FILE *fp;

        if ((fp = fopen(path, "rb")) == NULL) {
                throw Util::InitException (std::string ("pngLoad : couldn't open PNG file : ") + path);
        }

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

        /* If we have already read some of the signature */
        png_set_sig_bytes(png_ptr, sig_read);

        /* Read PNG header info */
        png_read_info (png_ptr, info_ptr);
        png_get_IHDR (png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);

        /* tell libpng to strip 16 bit/color files down to 8 bits/color */
        png_set_strip_16 (png_ptr);

        /* Extract multiple pixels with bit depths of 1, 2, and 4 from a single
         * byte into separate bytes (useful for paletted and grayscale images).
         */
        png_set_packing (png_ptr);

        /* scale greyscale values to the range 0..255 */
        if (color_type == PNG_COLOR_TYPE_GRAY) {
                png_set_expand (png_ptr);
        }

        volatile int ckey = -1;

        /*
         * For images with a single "transparent colour", set colour key;
         * if more than one index has transparency, or if partially transparent
         * entries exist, use full alpha channel
         */
        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
                int num_trans;
                unsigned char *trans;
//                ***TODO***
//                png_get_tRNS (png_ptr, info_ptr, &trans, &num_trans, &transv);

                if (color_type == PNG_COLOR_TYPE_PALETTE) {
                        /* Check if all tRNS entries are opaque except one */
                        int i, t = -1;

                        for (i = 0; i < num_trans; i++) {
                                if (trans[i] == 0) {
                                        if (t >= 0)
                                                break;
                                        t = i;
                                } else if (trans[i] != 255) {
                                        break;
                                }
                        }
                        if (i == num_trans) {
                                /* exactly one transparent index */
                                ckey = t;
                        } else {
                                /* more than one transparent index, or translucency */
                                png_set_expand(png_ptr);
                        }
                } else {
                        ckey = 0; /* actual value will be set later */
                }
        }

        if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
                png_set_gray_to_rgb (png_ptr);
        }

        png_read_update_info (png_ptr, info_ptr);
        png_get_IHDR (png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);

}

/****************************************************************************/

int checkIfPng (const char *file_name, FILE **fp)
{
        unsigned char buf[PNG_BYTES_TO_CHECK];

        /* Open the prospective PNG file. */
        if ((*fp = fopen(file_name, "rb")) == NULL)
                return 0;

        /* Read in some of the signature bytes */
        if (fread(buf, 1, PNG_BYTES_TO_CHECK, *fp) != PNG_BYTES_TO_CHECK)
                return 0;

        /* Compare the first PNG_BYTES_TO_CHECK bytes of the signature.
         Return nonzero (true) if they match */
        return (!png_sig_cmp(buf, (png_size_t) 0, PNG_BYTES_TO_CHECK));
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
