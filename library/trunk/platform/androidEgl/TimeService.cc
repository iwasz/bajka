/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID
#include "TimeService.h"

namespace Util {

uint32_t TimeService::getCurrentMs ()
{
        return 0;
}

/****************************************************************************/

void TimeService::delayMs (uint32_t)
{

}



} /* namespace Util */

#endif
