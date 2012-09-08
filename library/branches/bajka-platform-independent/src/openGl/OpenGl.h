/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IMPL_OPENGL_H_
#define BAJKA_IMPL_OPENGL_H_

/**
 * Inkluduje nagłówki OpenGL zależne od platformy.
 */

#if defined (LINUX)
#include <GL/gl.h>
#elif defined (ANDROID)
#include <GLES/gl.h>
#endif

#include "view/draw/Color.h"

namespace View {

extern void clear (View::Color const &c);

} /* namespace View */

#	endif /* OPENGL_H_ */
