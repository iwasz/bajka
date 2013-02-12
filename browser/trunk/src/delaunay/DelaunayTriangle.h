/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DELAUNAYTRIANGLE_H_
#define DELAUNAYTRIANGLE_H_

namespace Delaunay {

/**
 * Numbers triangle edges and vertices. Edge A (first edge) id at the opposite
 * side than vertex A.
 */
enum SideEnum { A = 1, B = 2, C = 3 };

/**
 * Default triangle type (index based).
 */
struct Triangle {

        typedef unsigned int IndexType;

        Triangle (IndexType x = 0, IndexType y = 0, IndexType z = 0) : a (x), b (y), c (z), tA (0), tB (0), tC (0) {}

        IndexType get (SideEnum s) const
        {
                switch (s) {
                case A:
                        return a;
                case B:
                        return b;
                case C:
                        return c;
                }
        }

        void set (SideEnum s, IndexType v)
        {
                switch (s) {
                case A:
                        a = v;
                        break;
                case B:
                        b = v;
                        break;
                case C:
                        c = v;
                        break;
                }
        }

        // Endpoints of a triangle.
        IndexType a, b, c;

        // Adjacent triangles (opposite side of a, b, c). TODO remove
        Triangle *tA, *tB, *tC;
};

} // namespace Delaunay

#endif /* DELAUNAYTRIANGLE_H_ */
