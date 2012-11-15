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

GLContext::GLContext () : currentPogramObject (0)
{
}

/****************************************************************************/

GLContext::~GLContext ()
{
        glDeleteProgram (currentPogramObject);
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
        currentPogramObject = linkProgram (vertexShader, fragmentShader);
        glUseProgram (currentPogramObject);
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
