/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#if defined (USE_OPENGL) || defined (USE_OPENGLES)
#include "OpenGl.h"
#include "util/Exceptions.h"

/****************************************************************************/

GLuint loadShader (GLenum type, const char *shaderSrc)
{
        GLuint shader;
        GLint compiled;

        // Create the shader object
        shader = glCreateShader (type);

        if (shader == 0) {
                throw Util::InitException ("loadShader : error loading shader.");
        }

        // Load the shader source
        glShaderSource (shader, 1, &shaderSrc, NULL);

        // Compile the shader
        glCompileShader (shader);

        // Check the compile status
        glGetShaderiv (shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
                GLint infoLen = 0;

                glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLen);

                if (infoLen > 1) {
                        char* infoLog = new char [infoLen];
                        glGetShaderInfoLog (shader, infoLen, NULL, infoLog);
                        std::string infoLogStr = infoLog;
                        delete [] infoLog;
                        throw Util::InitException (std::string ("loadShader : error compiling shader. Message : ") + infoLogStr);
                }

                glDeleteShader (shader);
                return 0;
        }

        return shader;
}

#endif
