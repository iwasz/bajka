/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_SDL
#include "TimeInterface.h"
#include <SDL.h>

namespace Util {

uint32_t TimeInterface::getCurrentMs ()
{
        return SDL_GetTicks ();
}

/****************************************************************************/

void TimeInterface::delayMs (uint32_t ms)
{
        SDL_Delay (ms);
}



} /* namespace Util */

#endif
