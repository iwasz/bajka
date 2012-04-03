/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID
#ifndef ANDROID_TIMEINTERFACE_H_
#define ANDROID_TIMEINTERFACE_H_

#include <stdint.h>

namespace Util {

struct TimeInterface {

        static uint32_t getCurrentMs ();
        static void delayMs (uint32_t);

};

} /* namespace Util */

#endif /* TIMEINTERFACE_H_ */
#endif
