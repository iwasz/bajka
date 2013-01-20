/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_JPEG
#include "Jpeg.h"
#include <cstdio>
#include <cstdlib>
#include <jpeglib.h>
#include <csetjmp>
#include <string>
#include "util/Exceptions.h"
#include "util/Math.h"

namespace View {

#define INPUT_BUFFER_SIZE 4096

struct myErrorMgr {
        struct jpeg_error_mgr pub; /* "public" fields */
        jmp_buf setjmp_buffer; /* for return to caller */
        std::string errorStringFromHandler;
};

typedef struct myErrorMgr *myErrorPtr;

static void myErrorExit (j_common_ptr cinfo);
static void myOutputMessage (j_common_ptr cinfo);
static void jpegDataSourceSrc (j_decompress_ptr cinfo, Common::DataSource *source);

/****************************************************************************/

void jpegLoad (Common::DataSource *source,
               void **data,
               int *widthOut,
               int *heightOut,
               int *visibleWidthOut,
               int *visibleHeightOut,
               ColorSpace *colorSpace,
               int *bitDepth,
               bool expandDimensions2)
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
                throw Util::InitException ("jpegLoad : an error occured : " + jerr.errorStringFromHandler);
        }

        /* Now we can initialize the JPEG decompression object. */
        jpeg_create_decompress (&cinfo);

        /* Step 2: specify data source (eg, a file) */

        jpegDataSourceSrc (&cinfo, source);

        /* Step 3: read file parameters with jpeg_read_header() */

        (void) jpeg_read_header (&cinfo, TRUE);

        if (expandDimensions2) {
                cinfo.out_color_space = JCS_EXT_RGBA;
                *colorSpace = RGBA;
        }
        else {
                cinfo.out_color_space = JCS_EXT_RGB;
                *colorSpace = RGB;
        }

        /* Step 5: Start decompressor */

        (void) jpeg_start_decompress (&cinfo);
        /* We can ignore the return value since suspension is not possible
         * with the stdio data source.
         */

        if (expandDimensions2) {
                *widthOut = Util::nextSqr (cinfo.output_width);
                *heightOut = Util::nextSqr (cinfo.output_height);
        }
        else {
                *widthOut = cinfo.output_width;
                *heightOut = cinfo.output_height;
        }

        *visibleWidthOut = cinfo.output_width;
        *visibleHeightOut = cinfo.output_height;
        *bitDepth = BITS_IN_JSAMPLE;

        // BITS_IN_JSAMPLE musi być równe 8
        *data = malloc (*widthOut * *heightOut * (BITS_IN_JSAMPLE / 8) * cinfo.output_components);

        if (!data) {
                throw Util::InitException("pngLoad : out of memory");
        }

        /* JSAMPLEs per row in output buffer */
        int scanLineLen = *widthOut * (BITS_IN_JSAMPLE / 8) * cinfo.output_components;
#ifdef BOTTOM_PLACEMENT
        int shiftYBytes = (*heightOut - *visibleHeightOut) * scanLineLen;
#endif
        JSAMPROW rowptr;

        while (cinfo.output_scanline < cinfo.output_height) {
                rowptr = ((JSAMPROW)*data) + cinfo.output_scanline * scanLineLen
#ifdef BOTTOM_PLACEMENT
                                + shiftYBytes
#endif
                                ;
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
}

/****************************************************************************/

bool checkIfJpeg (Common::DataSource *source)
{
        int start;
        bool is_JPG;
        bool in_scan;
        unsigned char magic[4];

        if (!source) {
                return false;
        }

        start = source->tell ();
        is_JPG = false;
        in_scan = false;

        if (source->read (magic, 2)) {

                if ((magic[0] == 0xFF) && (magic[1] == 0xD8)) {
                        is_JPG = true;

                        while (is_JPG) {
                                if (source->read (magic, 2) != 2) {
                                        is_JPG = false;
                                }
                                else if ((magic[0] != 0xFF) && (in_scan == false)) {
                                        is_JPG = false;
                                }
                                else if ((magic[0] != 0xFF) || (magic[1] == 0xFF)) {
                                        /* Extra padding in JPEG (legal) */
                                        /* or this is data and we are scanning */
                                        source->seek (-1, SEEK_CUR);
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
                                else if (source->read (magic + 2, 2) != 2) {
                                        is_JPG = false;
                                }
                                else {
                                        /* Yes, it's big-endian */
                                        unsigned int start2;
                                        unsigned int size2;
                                        unsigned int end2;
                                        start2 = source->tell ();
                                        size2 = (magic[2] << 8) + magic[3];
                                        end2 = source->seek (size2 - 2, SEEK_CUR);

                                        if (end2 != start2 + size2 - 2)
                                                is_JPG = false;

                                        if (magic[1] == 0xDA) {
                                                break;
                                        }
                                }
                        }
                }
        }

        source->seek (start, SEEK_SET);
        return is_JPG;
}

/****************************************************************************/

struct MySourceMgr {

        MySourceMgr () : source (NULL) {}
        struct jpeg_source_mgr pub;
        Common::DataSource *source;
        unsigned char buffer[INPUT_BUFFER_SIZE];
};

/*
 * Initialize source --- called by jpeg_read_header
 * before any data is actually read.
 */
static void init_source (j_decompress_ptr cinfo)
{
        /* We don't actually need to do anything */
        return;
}

/*
 * Fill the input buffer --- called whenever buffer is emptied.
 */
static boolean fill_input_buffer (j_decompress_ptr cinfo)
{
        MySourceMgr *src = (MySourceMgr *)cinfo->src;
        Common::DataSource *source = src->source;
        int nbytes = source->read (src->buffer, INPUT_BUFFER_SIZE);

        if (nbytes == 0) {
                /* Insert a fake EOI marker */
                src->buffer[0] = (unsigned char) 0xFF;
                src->buffer[1] = (unsigned char) JPEG_EOI;
                nbytes = 2;
        }

        src->pub.next_input_byte = src->buffer;
        src->pub.bytes_in_buffer = nbytes;

        return TRUE;
}

/*
 * Skip data --- used to skip over a potentially large amount of
 * uninteresting data (such as an APPn marker).
 *
 * Writers of suspendable-input applications must note that skip_input_data
 * is not granted the right to give a suspension return.  If the skip extends
 * beyond the data currently in the buffer, the buffer can be marked empty so
 * that the next read will cause a fill_input_buffer call that can suspend.
 * Arranging for additional bytes to be discarded before reloading the input
 * buffer is the application writer's problem.
 */
static void skip_input_data (j_decompress_ptr cinfo, long num_bytes)
{
        MySourceMgr * src = (MySourceMgr *) cinfo->src;

        /* Just a dumb implementation for now.  Could use fseek() except
         * it doesn't work on pipes.  Not clear that being smart is worth
         * any trouble anyway --- large skips are infrequent.
         */
        if (num_bytes > 0) {
                while (num_bytes > (long) src->pub.bytes_in_buffer) {
                        num_bytes -= (long) src->pub.bytes_in_buffer;
                        (void) src->pub.fill_input_buffer(cinfo);
                        /* note we assume that fill_input_buffer will never
                         * return FALSE, so suspension need not be handled.
                         */
                }
                src->pub.next_input_byte += (size_t) num_bytes;
                src->pub.bytes_in_buffer -= (size_t) num_bytes;
        }
}

/*
 * Terminate source --- called by jpeg_finish_decompress
 * after all data has been read.
 */
static void term_source (j_decompress_ptr cinfo)
{
        /* We don't actually need to do anything */
        return;
}

/**
 * Inicjująca zamiast jpeg_stdio_src
 */
static void jpegDataSourceSrc (j_decompress_ptr cinfo, Common::DataSource *source)
{
        MySourceMgr *src = NULL;

        /* The source object and input buffer are made permanent so that a series
         * of JPEG images can be read from the same file by calling jpeg_stdio_src
         * only before the first one.  (If we discarded the buffer at the end of
         * one image, we'd likely lose the start of the next one.)
         * This makes it unsafe to use this manager and a different source
         * manager serially with the same JPEG object.  Caveat programmer.
         */
        if (cinfo->src == NULL) { /* first time for this JPEG object? */
                cinfo->src = (struct jpeg_source_mgr *) (*cinfo->mem->alloc_small) (
                                (j_common_ptr) cinfo,
                                JPOOL_PERMANENT,
                                sizeof(MySourceMgr));

                src = (MySourceMgr *) cinfo->src;
        }

        src = (MySourceMgr *) cinfo->src;
        src->pub.init_source = init_source;
        src->pub.fill_input_buffer = fill_input_buffer;
        src->pub.skip_input_data = skip_input_data;
        src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
        src->pub.term_source = term_source;
        src->source = source;
        src->pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
        src->pub.next_input_byte = NULL; /* until buffer loaded */
}

/****************************************************************************/

static void myErrorExit (j_common_ptr cinfo)
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

static void myOutputMessage (j_common_ptr cinfo)
{
        char buffer[JMSG_LENGTH_MAX];

        /* Create the message */
        (*cinfo->err->format_message) (cinfo, buffer);

        /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
        myErrorPtr myerr = (myErrorPtr) cinfo->err;
        myerr->errorStringFromHandler = buffer;
}

} /* namespace View */
#endif
