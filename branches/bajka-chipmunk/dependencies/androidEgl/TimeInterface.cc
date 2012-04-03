/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID
#include "TimeInterface.h"

namespace Util {

uint32_t TimeInterface::getCurrentMs ()
{
        return 0;
}

/****************************************************************************/

void TimeInterface::delayMs (uint32_t)
{

}



} /* namespace Util */

#endif
