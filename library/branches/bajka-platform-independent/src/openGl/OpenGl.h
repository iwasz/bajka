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
#include <GL/glew.h>
#elif defined (ANDROID)
#include <GLES2/gl2.h>
#endif

extern GLuint loadShader (GLenum type, const char *shaderSrc);

#	endif /* OPENGL_H_ */
