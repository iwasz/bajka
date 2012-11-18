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

        /**
         * Aktualny program.
         */
        GLuint getCurrentProgramObject () const { return currentProgramObject; }
        GLint getColorUniformLocation () const { return colorUniformLocation; }
        GLint getPositionAttribLocation () const { return positionAttribLocation; }
        GLint getModelViewLocation () const { return modelViewLocation; }
        GLint getProjectionLocation () const { return projectionLocation; }
        Geometry::ProjectionMatrix const &getProjectionMatrix () const { return projection; }

private:

        void initProjectionMatrix (Util::Config *config);

private:

        Geometry::AffineMatrixVector matrixStack;
        GLuint currentProgramObject;
        GLint colorUniformLocation;
        GLint positionAttribLocation;
        GLint modelViewLocation;
        GLint projectionLocation;
        Geometry::ProjectionMatrix projection;

};

} /* namespace Common */
#endif /* GLCONTEXT_H_ */
