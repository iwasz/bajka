/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Platform.h>
#include <errno.h>
#include <time.h>
#include <android/log.h>
#include <util/Exceptions.h>

namespace U = Util;

/****************************************************************************/

uint32_t getCurrentMs ()
{
        timespec ts;

        if (clock_gettime (CLOCK_MONOTONIC, &ts) == -1) {
                throw U::RuntimeException ("clock_gettime (CLOCK_MONOTONIC) failed");
        }

        return ts.tv_sec * 1000 + ts.tv_nsec / 1000.0;
}

/****************************************************************************/

void delayMs (uint32_t ms)
{
        timespec req, res;

        req.tv_sec = ms / 1000;
        req.tv_nsec = (ms % 1000) * 1000;

        if (nanosleep (&req, &res) == -1) {
                throw U::RuntimeException ("nanosleep (&req, &res) failed");
        }
}

/****************************************************************************/

int printlog (const char *format, ...)
{
        va_list args;
        va_start(args, format);
        int ret = __android_log_vprint (ANDROID_LOG_INFO, "bajka", format, args);
        va_end(args);
        return ret;
}

