/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_SDL
#ifndef SDL_TIMEINTERFACE_H_
#define SDL_TIMEINTERFACE_H_

#include <stdint.h>

namespace Util {

struct TimeInterface {

        static uint32_t getCurrentMs ();
        static void delayMs (uint32_t);

};

} /* namespace Util */

#endif /* TIMEINTERFACE_H_ */
#endif
