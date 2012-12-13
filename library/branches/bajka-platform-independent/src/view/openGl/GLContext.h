/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_GLCONTEXT_H_
#define BAJKA_VIEW_GLCONTEXT_H_

#include "geometry/AffineMatrix.h"
#include "OpenGlPriv.h"
#include "geometry/ProjectionMatrix.h"

namespace Util {
class Config;
}

namespace View {

/**
 * Zmienne stanowe dla OpenGL ES 2.0
 */
class GLContext {
public:

        GLContext ();
        ~GLContext ();

        /**
         * Inicjuje.
         */
        void init (Util::Config *config);
        void initProjectionMatrix (Util::Config *config);

        /**
         * Pobiera macierz z góry stosu za pomocą getCurrentMatrix, moży ją przez m i
         * umieszcza wynik jako nowy wierzchołek stosu.
         */
        Geometry::AffineMatrix const &pushMatrix (Geometry::AffineMatrix const &m);

        /**
         * Zdejmuje wierzchołek stosu.
         */
        void popMatrix ();

        /**
         * Wierchołek stosu.
         */
        Geometry::AffineMatrix const &getCurrentMatrix () const;
        Geometry::ProjectionMatrix const &getProjectionMatrix () const { return projection; }

        /**
         * Wspołrzędne myszy na wspołrzedne projekcji (clip coordinates, czy jak one tam...)
         */
        void mouseToDisplay (float x, float y, float *nx, float *ny) const;

public:

        /// To jest tylko do odczytu - nie należy przyopisywać nic do tych pól.
        GLuint currentProgramObject;
        GLint colorUniformLocation;
        GLint positionAttribLocation;
        GLint modelViewLocation;
        GLint projectionLocation;
        GLint texCoordInAttribLocation;

private:

        Geometry::AffineMatrixVector matrixStack;
        Geometry::ProjectionMatrix projection;
//        Geometry::ProjectionMatrix projectionInverted;
        Util::Config *config;

};

} /* namespace Common */
#endif /* GLCONTEXT_H_ */
