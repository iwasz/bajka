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

GLContext::GLContext () :
        currentProgramObject (0),
        colorUniformLocation (0),
        positionAttribLocation (0),
        modelViewLocation (0),
        projectionLocation (0)
{
}

/****************************************************************************/

GLContext::~GLContext ()
{
        glDeleteProgram (currentProgramObject);
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

        GLuint vertexShader = loadShader (GL_VERTEX_SHADER, config->vertex.c_str());
        GLuint fragmentShader = loadShader (GL_FRAGMENT_SHADER, config->fragment.c_str());
        currentProgramObject = linkProgram (vertexShader, fragmentShader);
        glUseProgram (currentProgramObject);

        colorUniformLocation = glGetUniformLocation (currentProgramObject, "color");
        modelViewLocation = glGetUniformLocation (currentProgramObject, "modelView");
        projectionLocation = glGetUniformLocation (currentProgramObject, "projection");
        positionAttribLocation = glGetAttribLocation (currentProgramObject, "position");

        initProjectionMatrix (config);
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

/****************************************************************************/

void GLContext::initProjectionMatrix (Util::Config *config)
{
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

        projection.setViewport (-rX, rX, -rY, rY);
}

} /* namespace Common */
