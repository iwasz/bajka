/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL.h>
#include <stdint.h>

uint32_t getCurrentMs ()
{
        return SDL_GetTicks ();
}

/****************************************************************************/

void delayMs (uint32_t ms)
{
        SDL_Delay (ms);
}
