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
#include "util/Config.h"

/****************************************************************************/
/*
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
*/

/****************************************************************************/

void initOpenGl (Util::Config *config)
{
#ifndef ANDROID
        glewInit();

        if (!GLEW_VERSION_2_0) {
                throw Util::InitException ("OpenGL 2.0 not available");
        }
#endif

        glShadeModel(GL_FLAT);
        glDisable (GL_DEPTH_TEST);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        /*
         * Alpha blending. Niestety tekstura jest w niektorych miejscach
         * przezroczysta, ale wystaje spodniej niebieski kolor prostokątu.
         */
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        float aspectRatio = double (config->viewportHeight) / config->viewportWidth;
        float rX = config->projectionWidth / 2;
        float rY;

        if (config->projectionHeight == 0) {
                rY = rX * aspectRatio;
                config->projectionHeight = rY * 2;
        }
        else {
                rY = config->projectionHeight / 2;
        }

        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        gluOrtho2D (-rX, rX, -rY, rY);
        glPointSize (3);

        // glDrawArrays
        glEnableClientState(GL_VERTEX_ARRAY);
}

/****************************************************************************/

void freeOpenGl ()
{

}

/****************************************************************************/

void mouseToDisplay (int x, int y, int windowWidth, int windowHeight, float *nx, float *ny)
{
        GLdouble model[16];
        glGetDoublev (GL_MODELVIEW_MATRIX, model);

        GLdouble proj[16];
        glGetDoublev (GL_PROJECTION_MATRIX, proj);

        GLint view[4];
        glGetIntegerv (GL_VIEWPORT, view);

        GLdouble mx, my, mz;
        gluUnProject(x, windowHeight - y, 0.0f, model, proj, view, &mx, &my, &mz);
        *nx = mx;
        *ny = my;
}

#endif
