/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "GLContext.h"
#include <boost/numeric/ublas/matrix.hpp>
#include "util/Exceptions.h"
#include "util/Config.h"

namespace View {
using namespace boost::numeric::ublas;

/****************************************************************************/

GLContext::GLContext () : mainProgramObject (0)
{
}

/****************************************************************************/

GLContext::~GLContext ()
{
        glDeleteProgram (mainProgramObject);
}

/****************************************************************************/

void GLContext::init (Util::Config *config)
{
#ifndef ANDROID
        glewInit();

        if (!GLEW_VERSION_2_0) {
                throw Util::InitException ("OpenGL 2.0 not available");
        }
#endif

        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint programObject;
        GLint linked;

        const char *vertex =
"attribute vec4 position;                                "
"                                                        "
"varying vec2 texcoord;                                  "
"                                                        "
"void main()                                             "
"{                                                       "
"    gl_Position = position;             "
"    texcoord = position.xy * vec2(0.5) + vec2(0.5);        "
"}                                                       ";

        const char *fragment =
"uniform float fade_factor;                              "
"uniform sampler2D textures[2];                          "
"                                                        "
"varying vec2 texcoord;                                  "
"                                                        "
"void main()                                             "
"{                                                       "
"    gl_FragColor = mix(                                 "
"        texture2D(textures[0], texcoord),               "
"        texture2D(textures[1], texcoord),               "
"        fade_factor                                     "
"    );                                                  "
"}                                                       ";

        // Load the vertex/fragment shaders
//        vertexShader = loadShader (GL_VERTEX_SHADER, vertex);
//        fragmentShader = loadShader (GL_FRAGMENT_SHADER, fragment);
        vertexShader = loadShader (GL_VERTEX_SHADER, config->vertex.c_str());
        fragmentShader = loadShader (GL_FRAGMENT_SHADER, config->fragment.c_str());

        // Create the program object
        programObject = glCreateProgram ();

        if (programObject == 0)
                return;

        glAttachShader (programObject, vertexShader);
        glAttachShader (programObject, fragmentShader);

        // Bind vPosition to attribute 0
        glBindAttribLocation (programObject, 0, "vPosition");

        // Link the program
        glLinkProgram (programObject);

        // Check the link status
        glGetProgramiv (programObject, GL_LINK_STATUS, &linked);

        if (!linked) {
                GLint infoLen = 0;

                glGetProgramiv (programObject, GL_INFO_LOG_LENGTH, &infoLen);

                if (infoLen > 1) {
                        char* infoLog = new char [infoLen];
                        glGetProgramInfoLog (programObject, infoLen, NULL, infoLog);
                        std::string infoLogStr = infoLog;
                        delete [] infoLog;
                        throw Util::InitException (std::string ("loadShader : error linking program. Message : ") + infoLogStr);
                }

                glDeleteProgram (programObject);
                throw Util::InitException ("loadShader : error linking program.");
        }

        // Store the program object
        mainProgramObject = programObject;
        glUseProgram (mainProgramObject);
}

/****************************************************************************/

Geometry::AffineMatrix const &GLContext::pushMatrix (Geometry::AffineMatrix const &m)
{
        if (matrixStack.empty ()) {
                matrixStack.push_back (m);
                return matrixStack.back ();
        }

        Geometry::AffineMatrix const &top = matrixStack.back ();
        matrixStack.push_back (prod (top, m));
        return matrixStack.back ();
}

/****************************************************************************/

void GLContext::popMatrix ()
{
        if (matrixStack.empty ()) {
                throw Util::RuntimeException ("GLContext::popMatrix : matrixStack is empty!");
        }

        matrixStack.pop_back ();
}

/****************************************************************************/

Geometry::AffineMatrix const &GLContext::getCurrentMatrix () const
{
        if (matrixStack.empty ()) {
                return Geometry::AffineMatrix::UNITARY;
        }

        return matrixStack.back ();
}

} /* namespace Common */
