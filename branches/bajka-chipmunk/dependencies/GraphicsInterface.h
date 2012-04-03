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
#include "sdl/GraphicsInterface.h"
#elif defined (ANDROID)
#include "androidEgl/GraphicsInterface.h"
#endif

#	endif /* GRAPHICSINTERFACE_H_ */
