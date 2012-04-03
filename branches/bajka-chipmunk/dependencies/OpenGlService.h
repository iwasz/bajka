/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMPL_OPENGLSERVICE_H_
#define IMPL_OPENGLSERVICE_H_

#if defined (USE_OPENGL)
#include "openGl/OpenGlService.h"
#elif defined (USE_OPENGLES)
#include "openGlEs/OpenGlService.h"
#endif

#	endif /* OPENGLSERVICE_H_ */
