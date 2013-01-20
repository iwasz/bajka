/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cstdarg>
#include <cstdio>
#include <SDL.h>
#include <stdint.h>
#include <Platform.h>
#include <common/dataSource/DataSource.h>

int printlogImpl (const char *format, ...)
{
        va_list args;
        va_start (args, format);
        int ret = vprintf (format, args);
        va_end (args);
        return ret;
}

uint32_t getCurrentMs ()
{
        return SDL_GetTicks ();
}

/****************************************************************************/

void delayMs (uint32_t ms)
{
        SDL_Delay (ms);
}

/****************************************************************************/

Common::DataSource *newDataSource ()
{
        return new Common::DataSource ();
}

/****************************************************************************/

void deleteDataSource (Common::DataSource *ds)
{
        delete ds;
}

/****************************************************************************/

void quit ()
{
        printlog ("Quit request by user");
        exit (0);
}
