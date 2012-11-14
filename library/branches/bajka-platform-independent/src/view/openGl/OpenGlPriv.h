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

//extern GLuint loadShader (GLenum type, const char *shaderSrc);
extern void initOpenGl (Util::Config *config);
extern void freeOpenGl ();
extern void mouseToDisplay (int x, int y, int windowWidth, int windowHeight, float *nx, float *ny);
extern GLuint loadShader (GLenum type, const char *shaderSrc);

#	endif /* OPENGL_H_ */
