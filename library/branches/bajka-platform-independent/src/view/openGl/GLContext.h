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

namespace View {

/**
 * Zmienne stanowe dla OpenGL ES 2.0
 */
class GLContext {
public:

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

private:

        Geometry::AffineMatrixVector matrixStack;
//        GLuint mainProgramObject;

};

} /* namespace Common */
#endif /* GLCONTEXT_H_ */
