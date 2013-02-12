/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DELAUNAYTRIANGULATIONTRAITS_H_
#define DELAUNAYTRIANGULATIONTRAITS_H_

#include "DelaunayTriangle.h"

// TODO wywalić
#include "geometry/Point.h"

namespace Delaunay {

/**
 *
 */
template<typename T>
struct TriangleTraits {
        typedef typename T::IndexType IndexType;

        static inline IndexType get (T const &triangle, SideEnum side)
        {
                return triangle.get (side);
        }
};

/**
 *
 */
template<typename T>
struct TriangleMutableTraits {
        typedef typename TriangleTraits <T>::IndexType IndexType;

        static inline void set (T &triangle, SideEnum side, IndexType value)
        {
                return triangle.set (side, value);
        }

        static inline T construct (IndexType a = 0, IndexType b = 0, IndexType c = 0)
        {
                return T (a, b, c);
        }
};

/**
 * TODO wywalić = Geometry::Point
 */
template <typename P = Geometry::Point, typename T = Triangle>
struct DelaunayTriangulationTraits {
        typedef P PointType;
        typedef T TriangleType;

        typedef TriangleTraits <TriangleType> TriangleTraitsType;
        typedef typename TriangleTraitsType::IndexType IndexType;
//        typedef typename PointType

};

} // namespace Delaunay

#endif /* DELAUNAYTRIANGULATIONTRAITS_H_ */
