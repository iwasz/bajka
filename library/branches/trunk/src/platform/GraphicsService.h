/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMPL_GRAPHICSINTERFACE_H_
#define IMPL_GRAPHICSINTERFACE_H_

#if defined (LINUX)
#include "sdl/GraphicsService.h"
#elif defined (ANDROID)
#include "androidEgl/GraphicsService.h"
#endif

#	endif /* GRAPHICSINTERFACE_H_ */
