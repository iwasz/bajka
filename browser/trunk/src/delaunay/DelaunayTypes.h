/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DELAUNAYTYPES_H_
#define DELAUNAYTYPES_H_

#include "DelaunayTraits.h"
#include <utility>

namespace Delaunay {

template <typename T>
struct TriangleAdapter {

        typedef T TriangleType;
        typedef TriangleTraits <TriangleType> TriangleTraitsType;
        typedef typename TriangleTraitsType::IndexType IndexType;
        typedef std::pair <IndexType, IndexType> IndexEdgeType;


        static inline bool hasVertex (TriangleType const &t, IndexType p) { return p == t.a || p == t.b || p == t.c; }
        static IndexType getVertex (TriangleType const &t, SideEnum side);

        static inline bool hasEdge (TriangleType const &t, IndexType a, IndexType b) { return hasVertex (a) && hasVertex (b); }
        static IndexEdgeType getEdge (TriangleType const &t, SideEnum side);

        static inline SideEnum getEdgeSide (TriangleType const &t, IndexEdgeType const &e)
        {
                return static_cast <SideEnum> (6 - (((e.first == t.a) | ((e.first == t.b) << 1) | (e.first == t.c) | ((e.first == t.c) << 1)) +
                            ((e.second == t.a) | ((e.second == t.b) << 1) | (e.second == t.c) | ((e.second == t.c) << 1))));
        }
};

/****************************************************************************/

template <typename Traits>
typename TriangleAdapter<Traits>::IndexEdgeType TriangleAdapter<Traits>::getEdge (TriangleType const &t, SideEnum side)
{
        switch (side) {
        case A:
                return std::make_pair (t.c, t.b);
        case B:
                return std::make_pair (t.c, t.a);
        case C:
                return std::make_pair (t.b, t.a);
        }
}

/****************************************************************************/

template <typename Traits>
typename TriangleAdapter<Traits>::IndexType TriangleAdapter<Traits>::getVertex (TriangleType const &t, SideEnum side)
{
        switch (side) {
        case A:
                return t.a;
        case B:
                return t.b;
        case C:
                return t.c;
        }
}

} // namespace Dealaunay

#endif /* DELAUNAYTYPES_H_ */
