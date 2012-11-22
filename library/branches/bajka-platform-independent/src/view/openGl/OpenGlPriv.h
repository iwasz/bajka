/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IMPL_OPENGL_PRICV_H_
#define BAJKA_IMPL_OPENGL_PRICV_H_

/**
 * Inkluduje nagłówki OpenGL zależne od platformy.
 */

#if defined (LINUX)
#include <GL/glew.h>
#elif defined (ANDROID)
//#include <GLES2/gl2.h>
#include <GLES/gl.h>
#endif

namespace Util {
struct Config;
}

/**
 * Ładuje kod źródłowy i kompiluje shader. Zwraca uchwyt do niego.
 */
extern GLuint loadShader (GLenum type, const char *shaderSrc);

/**
 * Tworzy obiekt programu, podłącza shadery, linkuje i zwraca uchwyt do programu.
 */
extern GLuint linkProgram (GLuint vertexShader, GLuint fragmentShader);

#	endif /* OPENGL_H_ */
