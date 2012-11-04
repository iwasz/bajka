/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Jpeg.h"
#include <cstdio>
#include <cstdlib>
#include <jpeglib.h>
#include <csetjmp>
#include <string>
#include "util/Exceptions.h"
#include "util/Math.h"

namespace View {

struct myErrorMgr {
        struct jpeg_error_mgr pub; /* "public" fields */
        jmp_buf setjmp_buffer; /* for return to caller */
        std::string errorStringFromHandler;
};

typedef struct myErrorMgr *myErrorPtr;

/****************************************************************************/

METHODDEF(void) myErrorExit (j_common_ptr cinfo)
{
        /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
        myErrorPtr myerr = (myErrorPtr) cinfo->err;

        /* Always display the message. */
        /* We could postpone this until after returning, if we chose. */
        (*cinfo->err->output_message) (cinfo);

        /* Return control to the setjmp point */
        longjmp (myerr->setjmp_buffer, 1);
}

/****************************************************************************/

METHODDEF(void) myOutputMessage (j_common_ptr cinfo)
{
        char buffer[JMSG_LENGTH_MAX];

        /* Create the message */
        (*cinfo->err->format_message) (cinfo, buffer);

        /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
        myErrorPtr myerr = (myErrorPtr) cinfo->err;
        myerr->errorStringFromHandler = buffer;
}

/****************************************************************************/

void jpegLoad (void *source, void **data, int *widthOut, int *heightOut, int *visibleWidthOut, int *visibleHeightOut, bool expandDimensions2)
{
        /* This struct contains the JPEG decompression parameters and pointers to
         * working space (which is allocated as needed by the JPEG library).
         */
        struct jpeg_decompress_struct cinfo;

        /* We use our private extension JPEG error handler.
         * Note that this struct must live as long as the main JPEG parameter
         * struct, to avoid dangling-pointer problems.
         */
        struct myErrorMgr jerr;
        FILE *infile = static_cast <FILE *> (source);

        /* Step 1: allocate and initialize JPEG decompression object */

        /* We set up the normal JPEG error routines, then override error_exit. */
        cinfo.err = jpeg_std_error (&jerr.pub);
        jerr.pub.error_exit = myErrorExit;
        jerr.pub.output_message = myOutputMessage;

        /* Establish the setjmp return context for my_error_exit to use. */
        if (setjmp (jerr.setjmp_buffer)) {
                /* If we get here, the JPEG code has signaled an error.
                * We need to clean up the JPEG object, close the input file, and return.
                */
                jpeg_destroy_decompress (&cinfo);
                fclose (infile);
                throw Util::InitException ("jpegLoad : an error occured : " + jerr.errorStringFromHandler);
        }

        /* Now we can initialize the JPEG decompression object. */
        jpeg_create_decompress (&cinfo);

        /* Step 2: specify data source (eg, a file) */

        jpeg_stdio_src (&cinfo, infile);

        /* Step 3: read file parameters with jpeg_read_header() */

        (void) jpeg_read_header (&cinfo, TRUE);

//        TODO To tylko narazie - zamieinć na zwykłe RGB.
        cinfo.out_color_space = JCS_EXT_RGBA;

        /* Step 5: Start decompressor */

        (void) jpeg_start_decompress (&cinfo);
        /* We can ignore the return value since suspension is not possible
         * with the stdio data source.
         */

        if (expandDimensions2) {
                *widthOut = Util::Math::nextSqr (cinfo.output_width);
                *heightOut = Util::Math::nextSqr (cinfo.output_height);
        }
        else {
                *widthOut = cinfo.output_width;
                *heightOut = cinfo.output_height;
        }

        *visibleWidthOut = cinfo.output_width;
        *visibleHeightOut = cinfo.output_height;

        // BITS_IN_JSAMPLE musi być równe 8
        *data = malloc (*widthOut * *heightOut * (BITS_IN_JSAMPLE / 8) * cinfo.output_components);

        if (!data) {
                throw Util::InitException("pngLoad : out of memory");
        }

        /* JSAMPLEs per row in output buffer */
        int scanLineLen = *widthOut * (BITS_IN_JSAMPLE / 8) * cinfo.output_components;
        int shiftYBytes = (*heightOut - *visibleHeightOut) * scanLineLen;
        JSAMPROW rowptr;

        while (cinfo.output_scanline < cinfo.output_height) {
                rowptr = ((JSAMPROW)*data) + shiftYBytes + cinfo.output_scanline * scanLineLen;
                (void) jpeg_read_scanlines (&cinfo, &rowptr, 1);
        }

        /* Step 7: Finish decompression */

        (void) jpeg_finish_decompress (&cinfo);
        /* We can ignore the return value since suspension is not possible
         * with the stdio data source.
         */

        /* Step 8: Release JPEG decompression object */

        /* This is an important step since it will release a good deal of memory. */
        jpeg_destroy_decompress (&cinfo);

        /* After finish_decompress, we can close the input file.
         * Here we postpone it until after no more JPEG errors are possible,
         * so as to simplify the setjmp error logic above.  (Actually, I don't
         * think that jpeg_destroy can do an error exit, but why assume anything...)
         */
        fclose (infile);
}

/****************************************************************************/

bool checkIfJpeg (void *source)
{
        int start;
        bool is_JPG;
        bool in_scan;
        unsigned char magic[4];

        if (!source) {
                return false;
        }

        FILE *src = static_cast <FILE *> (source);

        start = ftell (src);
        is_JPG = false;
        in_scan = false;

        if (fread (magic, 2, 1, src)) {

                if ((magic[0] == 0xFF) && (magic[1] == 0xD8)) {
                        is_JPG = true;

                        while (is_JPG) {
                                if (fread (magic, 1, 2, src) != 2) {
                                        is_JPG = false;
                                }
                                else if ((magic[0] != 0xFF) && (in_scan == false)) {
                                        is_JPG = false;
                                }
                                else if ((magic[0] != 0xFF) || (magic[1] == 0xFF)) {
                                        /* Extra padding in JPEG (legal) */
                                        /* or this is data and we are scanning */
                                        fseek (src, -1, SEEK_CUR);
                                }
                                else if (magic[1] == 0xD9) {
                                        /* Got to end of good JPEG */
                                        break;
                                }
                                else if ((in_scan == false) && (magic[1] == 0x00)) {
                                        /* This is an encoded 0xFF within the data */
                                }
                                else if ((magic[1] >= 0xD0) && (magic[1] < 0xD9)) {
                                        /* These have nothing else */
                                }
                                else if (fread (magic + 2, 1, 2, src) != 2) {
                                        is_JPG = false;
                                }
                                else {
                                        /* Yes, it's big-endian */
                                        unsigned int start2;
                                        unsigned int size2;
                                        unsigned int end2;
                                        start2 = ftell (src);
                                        size2 = (magic[2] << 8) + magic[3];
                                        fseek (src, size2 - 2, SEEK_CUR);
                                        end2 = ftell (src);

                                        if (end2 != start2 + size2 - 2)
                                                is_JPG = false;

                                        if (magic[1] == 0xDA) {
                                                break;
                                        }
                                }
                        }
                }
        }

        fseek (src, start, SEEK_SET);
        return is_JPG;
}

} /* namespace View */
