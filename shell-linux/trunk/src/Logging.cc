/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cstdarg>
#include <cstdio>

int log (const char *format, ...)
{
        va_list args;
        va_start (args, format);
        int ret = vprintf (format, args);
        va_end (args);
        return ret;
}
