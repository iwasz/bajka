/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DELAUNAYINDEX_H_
#define DELAUNAYINDEX_H_

#include "DelaunayTypes.h"
#include "DelaunayTriangle.h"
#include <vector>

namespace Delaunay {

template <typename Input, typename Traits = DelaunayTriangulationTraits <> >
class DelaunayIndex {
public:

        typedef typename Traits::PointType PointType;

        typedef typename Traits::TriangleType TriangleType;
        typedef std::vector <TriangleType> TriangleVector;

        // Data structure not optimized. Maybe some contiguous memory region can be used to eliminate memory partition and std::vector overhead.
        typedef std::vector <TriangleType const *> TrianglePtrVector;
        typedef std::vector <TrianglePtrVector> TriangleIndex;

        DelaunayIndex (Input const &i) : input (i)
        {
                triangleIndex.resize (input.size ());
                // TODO ***KRYTYCZNE*** ustawić tu tyle ile ma być. Da się to wyliczyć na początku!?
                triangulation.reserve (input.size () * 10);
        }

        TriangleType *getAdjacentTriangle (TriangleType const &triangle, SideEnum side);


        /**
         * Returns if diagonal (a, b) lays completely inside the polygon. It assumes two things:
         * - Points in polygon are stored in counter clockwise order.
         * - Checked diagonal do not intersects with boundary segments (defined by polygon itself)
         * in points other than a and b.
         * This second condition is easy to conform to, since we operate on diagonals generated
         * by triangulation algotihm.
         */
        bool diagonalInside (const Geometry::Point& a,
                             const Geometry::Point& ap,
                             const Geometry::Point& an,
                             const Geometry::Point& b) const;

        /**
         * Input : this->triangulation (performed earlier), edge to check for. Edge must have endpoints
         * in this->input.
         * Output : list of edges which intersects with edge.
         */
        void findCrossingEdges (Edge const &edge, CrossingEdgeList *crossingEdges, TrianglePtrVector *crossingTriangles) const;

        /**
         * First tuple element : number of intersections (0, 1 or 2).
         * Second tuple element : number of first edge (if any) which intersects with edge e.
         * Third tuple element : number of second edge (if any) which intersects with edge e.
         * - 1 : c-b
         * - 2 : c-a
         * - 3 : b-a
         */
        boost::tuple <int, int, int> intersects (Triangle const &t, Geometry::Edge const &e) const;

        /**
         * Are two adjacent triangles form quadrilateral which is convex?
         */
        bool twoTrianglesConvex (CrossingEdge const &c) const;

        Geometry::Edge indexEdgeToEdge (Edge const &e) const
        {
                Geometry::Edge f;
                f.a = input[e.first];
                f.b = input[e.second];
                return f;
        }

private:

        Input const &input;
        TriangleVector triangulation;
        TriangleIndex triangleIndex;

};

/****************************************************************************/

template <typename Traits>
typename DelaunayIndex <Traits>::TriangleType *DelaunayIndex <Traits>::getAdjacentTriangle (TriangleType const &triangle, SideEnum side)
{
        switch (side) {
        case A:
                return triangle.tA;
        case B:
                return triangle.tB;
        case B:
                return triangle.tC;
        }
}

template <typename Input, typename Traits>
boost::tuple <int, int, int> DelaunayTriangulation<Input, Traits>::intersects (Triangle const &t, Geometry::Edge const &e) const
{
        boost::tuple <int, int, int> ret;

        int cnt = 0;
        Geometry::Edge edge;
        edge.a = input[t.c];
        edge.b = input[t.b];
        if (Geometry::intersects (e, edge)) {
                ret.get<1> () = 1;
                ++cnt;
        }

        edge.a = input[t.c];
        edge.b = input[t.a];
        if (Geometry::intersects (e, edge)) {
                if (cnt) {
                        ret.get<2> () = 2;
                }
                else {
                        ret.get<1> () = 2;
                }
                ++cnt;
        }

        edge.a = input[t.b];
        edge.b = input[t.a];
        if (Geometry::intersects (e, edge)) {
                if (cnt) {
                        ret.get<2> () = 3;
                }
                else {
                        ret.get<1> () = 3;
                }
                ++cnt;
        }

        ret.get<0> () = cnt;
        return ret;
}

/****************************************************************************/

template <typename Traits>
void DelaunayTriangulation<Traits>::findCrossingEdges (Edge const &edge, CrossingEdgeList *crossingEdges, TrianglePtrVector *triangles) const
{
        TrianglePtrVector const &incidentTriangles = triangleIndex[edge.first];
        Geometry::Edge e;
        e.a = input[edge.first];
        e.b = input[edge.second];

        Triangle const *start = NULL;
        boost::tuple <int, int, int> intersections;
        for (TrianglePtrVector::const_iterator k = incidentTriangles.begin (); k != incidentTriangles.end (); ++k) {
                intersections = intersects (**k, e);
                if (intersections.get<0> ()) {
                        start = *k;
                        break;
                }
        }

#if 0
        if (start) {
                std::cerr << "Missing constraint : (" << edge.first << "," << edge.second << "), first triangle intersecinting this constraint : " << *start << std::endl;
        }
#endif

        assert (start);

        if (triangles) {
                triangles->push_back (start);
        }

        int commonEdgeNumber = intersections.get<1> ();
        Triangle const *next = start;

        while (true) {
                Edge commonEdge = getTriangleEdge (*next, commonEdgeNumber);
                CrossingEdge crossingEdge;
                crossingEdge.get<0> () = commonEdge;
                crossingEdge.get<1> () = next;
                next = getAdjacentTriangle (*next, commonEdgeNumber);
                crossingEdge.get<2> () = next;
                commonEdgeNumber = getEdgeSide (*next, commonEdge);

                // Musi być, bo gdyby nie było, to by znaczyło, że constraint wychodzi poza zbiór punktów (ma jeden koniec gdzieś w powietrzu).
                assert (next);

                if (triangles) {
                        crossingEdges->push_back (crossingEdge);
                        triangles->push_back (next);
                }

                if (next->hasPoint (edge.second)) {
                        break;
                }

                intersections = intersects (*next, e);

                // Musi się przecinać w 2 punktach, bo inaczej by wyszło z funkcji.
                assert (intersections.get<0> () == 2);

                // Eliminate commonEdge from equation - we know about it already. Find new commonEdge.
                if (intersections.get<1> () == commonEdgeNumber) {
                        commonEdgeNumber = intersections.get<2> ();
                }
                else if (intersections.get<2> () == commonEdgeNumber) {
                        commonEdgeNumber = intersections.get<1> ();
                }
        }

}

/****************************************************************************/

bool DelaunayTriangulation::twoTrianglesConvex (CrossingEdge const &c) const
{
        Edge firstDiagonal = c.get<0> ();
        Triangle const *a = c.get<1> ();
        Triangle const *b = c.get<2> ();

        int aSide = getEdgeSide (*a, firstDiagonal);
        int bSide = getEdgeSide (*b, firstDiagonal);

        Edge secondDiagonal = std::make_pair (getTriangleVertex (*a, aSide), getTriangleVertex (*b, bSide));
        Geometry::Edge e1 = indexEdgeToEdge (firstDiagonal);
        Geometry::Edge e2 = indexEdgeToEdge (secondDiagonal);
        return Geometry::intersects (e1, e2);
}

/****************************************************************************/

bool DelaunayTriangulation::diagonalInside (Geometry::Point const &a, Geometry::Point const &ap, Geometry::Point const &an, Geometry::Point const &b) const
{
        return true;
        int apx = ap.x - a.x;
        int apy = ap.y - a.y;
        int anx = an.x - a.x;
        int any = an.y - a.y;
        int bx = b.x - a.x;
        int by = b.y - a.y;

        int apXan = apx * any - apy * anx;
        int apXb = apx * by - apy * bx;
        int bXan = bx * any - by * anx;

        return ((apXan >= 0 && apXb >= 0 && bXan >= 0) || (apXan < 0 && !(apXb < 0 && bXan < 0)));
}

/****************************************************************************/

} // namespace

#endif /* DELAUNAYINDEX_H_ */
