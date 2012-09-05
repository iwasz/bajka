/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMPL_TIMEINTERFACE_H_
#define IMPL_TIMEINTERFACE_H_

#if defined (LINUX)
#include "sdl/TimeService.h"
#elif defined (ANDROID)
#include "androidEgl/TimeService.h"
#endif

#	endif /* TIMEINTERFACE_H_ */
