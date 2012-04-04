/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_SDL
#include "TimeService.h"
#include <SDL.h>

namespace Util {

uint32_t TimeService::getCurrentMs ()
{
        return SDL_GetTicks ();
}

/****************************************************************************/

void TimeService::delayMs (uint32_t ms)
{
        SDL_Delay (ms);
}



} /* namespace Util */

#endif
