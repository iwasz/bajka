/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DELAUNAYTRIANGLEEDGE_H_
#define DELAUNAYTRIANGLEEDGE_H_

#include "DelaunayTriangle.h"

namespace Delaunay {

/**
 *
 */
template <typename T>
struct TriangleEdge {
        typedef T TriangleType;
        typedef TriangleTraits <TriangleType> TriangleTraitsType;
        typedef typename TriangleTraitsType::IndexType IndexType;

        TriangleEdge (IndexType a_ = 0, IndexType b_ = 0) : a (a_), b (b_) {}
        IndexType a, b;
};

/****************************************************************************/

template <typename T>
bool hasEdge (T const &t, TriangleEdge <T> const e)
{
        return hasVertex (e.a) && hasVertex (e.b);
}

/****************************************************************************/

template <typename T>
SideEnum getEdgeSide (T const &t, TriangleEdge <T> const &e)
{
        return static_cast <SideEnum> (6 - (((e.a == a (t)) | ((e.a == b (t)) << 1) | (e.a == c (t)) | ((e.a == c (t)) << 1)) +
                    ((e.b == a (t)) | ((e.b == b (t)) << 1) | (e.b == c (t)) | ((e.b == c (t)) << 1))));
}

/****************************************************************************/

template <typename T>
TriangleEdge<T> getEdge (T const &t, SideEnum side)
{
        switch (side) {
        case A:
                return TriangleEdge<T> (c (t), b (t));
        case B:
                return TriangleEdge<T> (c (t), a (t));
        case C:
                return TriangleEdge<T> (b (t), a (t));
        }
}

} // namespace Delaunay

#endif /* DELAUNAYTRIANGLEEDGE_H_ */
