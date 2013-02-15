/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DELAUNAYINDEX_H_
#define DELAUNAYINDEX_H_

#include "DelaunayTriangle.h"
#include "DelaunayPoint.h"
#include "DelaunayEdge.h"
#include "DelaunayTriangleEdge.h"
#include "DelaunayTraits.h"
#include <vector>
#include <list>
#include <boost/tuple/tuple.hpp>

namespace Delaunay {

/**
 * TODO operqacje
 * - addTriangle - dodaje do triangulacji i uaktualnia wszystkie indeksy.
 * - numTriangles - ile jest aktualnie trójkatów w triangulacji.
 * -
 */
template <typename Input, typename Traits = DelaunayTriangulationTraits <> >
class DelaunayIndex {
public:

        typedef typename Traits::PointType PointType;
        typedef PointTraits<PointType> PointTraitsType;
        typedef typename PointTraitsType::CoordinateType CoordinateType;
        typedef Edge <PointType> EdgeType;
        typedef typename Traits::TriangleType TriangleType;
        typedef TriangleTraits <TriangleType> TriangleTraitsType;
        typedef typename TriangleTraitsType::IndexType IndexType;
        typedef TriangleEdge<TriangleType> TriangleEdgeType;
        typedef std::vector <TriangleType> TriangleVector;
        typedef std::vector <TriangleType const *> TrianglePtrVector; // TODO Data structure not optimized. Maybe some contiguous memory region can be used to eliminate memory partition and std::vector overhead.
        typedef std::vector <TrianglePtrVector> TriangleIndex;
        typedef boost::tuple <TriangleEdgeType, TriangleType const *, TriangleType const *> CrossingEdge;
        typedef std::list <CrossingEdge> CrossingEdgeList;
        typedef boost::tuple <int, SideEnum, SideEnum> IntersectionInfo;

        DelaunayIndex (Input const &i) : input (i)
        {
                triangleIndex.resize (input.size ());
        }

        size_t getTriangleIndexSize () const { return triangleIndex.size (); }
        void addTriangle (IndexType index, TriangleType const *triangle);
        void addTriangle (TriangleType const *triangle);
        TrianglePtrVector const &getTrianglesForIndex (IndexType i) const { return triangleIndex[i]; }
        TrianglePtrVector &getTrianglesForIndex (IndexType i) { return triangleIndex[i]; }

        void setVertex (TriangleType &t, SideEnum s, IndexType v);

/****************************************************************************/

        TriangleType *getAdjacentTriangle (TriangleType const &triangle, SideEnum side);
        void setAdjacentTriangle (TriangleType &t, SideEnum s, TriangleType *a);

        /**
         * Input : this->triangulation (performed earlier), edge to check for. Edge must have endpoints
         * in this->input.
         * Output : list of edges which intersects with edge.
         */
        void findCrossingEdges (TriangleEdgeType const &edge, CrossingEdgeList *crossingEdges, TrianglePtrVector *crossingTriangles) const;

        /**
         * First tuple element : number of intersections (0, 1 or 2).
         * Second tuple element : number of first edge (if any) which intersects with edge e.
         * Third tuple element : number of second edge (if any) which intersects with edge e.
         * - 1 : c-b
         * - 2 : c-a
         * - 3 : b-a
         */
        IntersectionInfo intersects (TriangleType const &t, EdgeType const &e) const;

        /**
         * Are two adjacent triangles form quadrilateral which is convex?
         */
        bool twoTrianglesConvex (CrossingEdge const &c) const;

        /**
         * Perform a flip, and return new diagonal. Triangle index.
         */
        void flip (CrossingEdge const &c, TriangleEdgeType *newDiagonal);

        /**
         * Index based edge to coordinate based edge.
         */
        EdgeType triangleEdgeToEdge (TriangleEdgeType const &e) const
        {
                return EdgeType (input[e.a], input[e.b]);
        }

        /**
         *
         */
        void getTriaglesForEdge (TriangleEdgeType const &e, TriangleType **a, TriangleType **b);

private:

        Input const &input;
        TriangleIndex triangleIndex;

};

/****************************************************************************/

template <typename Input, typename Traits>
typename DelaunayIndex <Input, Traits>::TriangleType *
DelaunayIndex <Input, Traits>::getAdjacentTriangle (TriangleType const &triangle, SideEnum side)
{
        // TODO infromation about adjacent triangles shall be stored outside the Triangle itself. Some external vector is need.
        switch (side) {
        case A:
                return triangle.tA;
        case B:
                return triangle.tB;
        case C:
                return triangle.tC;
        default:
                return 0;
        }

}

template <typename Input, typename Traits>
void DelaunayIndex <Input, Traits>::setAdjacentTriangle (TriangleType &t, SideEnum s, TriangleType *a)
{
        switch (s) {
        case A:
                t.tA = a;
                break;
        case B:
                t.tB = a;
                break;
        case C:
                t.tC = a;
                break;
        default:
                break;
        }
}

/****************************************************************************/

template <typename Input, typename Traits>
typename DelaunayIndex<Input, Traits>::IntersectionInfo
DelaunayIndex<Input, Traits>::intersects (TriangleType const &t, EdgeType const &e) const
{
        IntersectionInfo ret;

        int cnt = 0;
        EdgeType edge = triangleEdgeToEdge (TriangleEdgeType (c (t), b (t)));

        if (Delaunay::intersects (e, edge)) {
                ret.get<1> () = A;
                ++cnt;
        }

        edge.a = input[t.c];
        edge.b = input[t.a];
        if (Delaunay::intersects (e, edge)) {
                if (cnt) {
                        ret.get<2> () = B;
                }
                else {
                        ret.get<1> () = B;
                }
                ++cnt;
        }

        edge.a = input[t.b];
        edge.b = input[t.a];
        if (Delaunay::intersects (e, edge)) {
                if (cnt) {
                        ret.get<2> () = C;
                }
                else {
                        ret.get<1> () = C;
                }
                ++cnt;
        }

        ret.get<0> () = cnt;
        return ret;
}

/****************************************************************************/

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::findCrossingEdges (TriangleEdgeType const &edge, CrossingEdgeList *crossingEdges, TrianglePtrVector *crossingTriangles) const
{
        TrianglePtrVector const &incidentTriangles = triangleIndex[edge.a];
        EdgeType e = triangleEdgeToEdge (edge);
        TriangleType const *start = NULL;
        IntersectionInfo intersections;

        for (typename TrianglePtrVector::const_iterator k = incidentTriangles.begin (); k != incidentTriangles.end (); ++k) {
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

        if (crossingTriangles) {
                crossingTriangles->push_back (start);
        }

        SideEnum commonEdgeNumber = intersections.get<1> ();
        Triangle const *next = start;

        while (true) {
                TriangleEdgeType commonEdge = getEdge (*next, commonEdgeNumber);
                CrossingEdge crossingEdge;
                crossingEdge.template get<0> () = commonEdge;
                crossingEdge.template get<1> () = next;
                // TODO - rozwiązać sprawę z const / nie cost.
                next = const_cast <DelaunayIndex *> (this)->getAdjacentTriangle (*next, commonEdgeNumber);
                crossingEdge.template get<2> () = next;
                commonEdgeNumber = getEdgeSide (*next, commonEdge);

                // Musi być, bo gdyby nie było, to by znaczyło, że constraint wychodzi poza zbiór punktów (ma jeden koniec gdzieś w powietrzu).
                assert (next);

                if (crossingTriangles) {
                        crossingEdges->push_back (crossingEdge);
                        crossingTriangles->push_back (next);
                }

                if (hasVertex (*next, edge.b)) {
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

template <typename Input, typename Traits>
bool DelaunayIndex<Input, Traits>::twoTrianglesConvex (CrossingEdge const &c) const
{
        TriangleEdgeType firstDiagonal = c.template get<0> ();
        TriangleType const *a = c.template get<1> ();
        TriangleType const *b = c.template get<2> ();

        SideEnum aSide = getEdgeSide (*a, firstDiagonal);
        SideEnum bSide = getEdgeSide (*b, firstDiagonal);

        TriangleEdgeType secondDiagonal = TriangleEdgeType (getVertex (*a, aSide), getVertex (*b, bSide));
        EdgeType e1 = triangleEdgeToEdge (firstDiagonal);
        EdgeType e2 = triangleEdgeToEdge (secondDiagonal);
        return Delaunay::intersects (e1, e2);
}

/****************************************************************************/

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::addTriangle (IndexType index, TriangleType const *triangle)
{
        assert (getTriangleIndexSize () > index);
        triangleIndex[index].push_back (triangle);
}

/****************************************************************************/

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::addTriangle (TriangleType const *triangle)
{
        addTriangle (a (*triangle), triangle);
        addTriangle (b (*triangle), triangle);
        addTriangle (c (*triangle), triangle);
}

/****************************************************************************/

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::flip (CrossingEdge const &cross, TriangleEdgeType *newDiagonal)
{
        TriangleEdgeType oldDiagonal = cross.template get<0> ();
//        TriangleType *f = const_cast <TriangleType *> (cross.template get<1> ()); // TODO get rid of const_cast!
//        TriangleType *s = const_cast <TriangleType *> (cross.template get<2> ()); // TODO get rid of const_cast!
//        TriangleType fCopy = *f;
//        TriangleType sCopy = *s;
        TriangleType *f = 0;
        TriangleType *s = 0;

        getTriaglesForEdge (oldDiagonal, &f, &s);


        std::cerr << "oldDiagonal : " << oldDiagonal << ", f : " << *f << ", s : " << *s << ", ptr : " << f << ", " << s << std::endl;
//        SideEnum fSide = getEdgeSide (*f, oldDiagonal);
//        IndexType fRemain = getVertex (*f, fSide);
//        SideEnum sSide = getEdgeSide (*s, oldDiagonal);
//        IndexType sRemain = getVertex (*s, sSide);

        SideEnum foa = getVertexSide (*f, oldDiagonal.a);
        SideEnum fob = getVertexSide (*f, oldDiagonal.b);
        SideEnum fc = otherThan (foa, fob);
        IndexType fcIndex = getVertex (*f, fc);

        std::cerr << "foa : " << (int)foa << ", fob : " << (int)fob << ", fc : " << (int)fc << ", fcIndex : " << fcIndex << std::endl;

        SideEnum soa = getVertexSide (*s, oldDiagonal.a);
        SideEnum sob = getVertexSide (*s, oldDiagonal.b);
        SideEnum sc = otherThan (soa, sob);
        IndexType scIndex = getVertex (*s, sc);

        std::cerr << "soa : " << (int)soa << ", sob : " << (int)sob << ", sc : " << (int)sc << ", scIndex : " << scIndex << std::endl;

        // TODO CCW sort of entire new triangle
        this->setVertex (*f, fob, scIndex);

//        krawędź fob - foa (czyli fc) <- trójkąt przylegly do sob - sc, czyli soa
//      krawędź fob -fc <- s
        setAdjacentTriangle (*f, fc, getAdjacentTriangle (*s, soa));
        setAdjacentTriangle (*f, foa, s);

        // TODO CCW sort of entire new triangle
        // TODO wywlić this i upewnic się, że nie bierze globalnej.
        this->setVertex (*s, sob, fcIndex);

        //// Krawędź
        setAdjacentTriangle (*s, sc, getAdjacentTriangle (*f, foa));
        setAdjacentTriangle (*s, foa, f);

        // TODO CCW sort
        newDiagonal->a = fcIndex;
        newDiagonal->b = scIndex;

        std::cerr << "newDiagonal : " << *newDiagonal << ", f : " << *f << ", s : " << *s << std::endl;

//        // TODO Order of vertices is random. FIX. CCW.
//        a (*f, fRemain);
//        b (*f, sRemain);
//        c (*f, oldDiagonal.a);
//        f->tC = s;
//
//        // TODO Order of vertices is random. FIX. CCW.
//        a (*s, sRemain);
//        b (*s, fRemain);
//        c (*s, oldDiagonal.b);
//        s->tC = f;
}

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::getTriaglesForEdge (TriangleEdgeType const &e, TriangleType **a, TriangleType **b)
{
        TrianglePtrVector const &triaglesA = triangleIndex[e.a];
        *a = *b = NULL;

        for (typename TrianglePtrVector::const_iterator i = triaglesA.begin (); i != triaglesA.end (); ++i) {
                Triangle const *t = *i;
                SideEnum s = getVertexSide (*t, e.a);
                TriangleEdgeType me = getEdge (*t, s);

                if (me.a == e.b || me.b == e.b) {
                        if (!*a) {
                                // TODO get rid od cast
                                *a = const_cast <TriangleType *> (t);
                        }
                        else if (!*b) {
                                *b = const_cast <TriangleType *> (t);
                                return;
                        }
                }
        }
}

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::setVertex (TriangleType &t, SideEnum s, IndexType v)
{
        IndexType current = Delaunay::getVertex (t, s);

        TrianglePtrVector &triangles = triangleIndex[current];
        triangles.erase (std::remove (triangles.begin (), triangles.end (), &t));

        Delaunay::setVertex (t, s, v);
        TrianglePtrVector trianglesV = triangleIndex[v];
        trianglesV.push_back (&t);
}

#if 0
#ifndef NDEBUG

template <>
std::ostream &operator<< (std::ostream &o, TriangleVector const &e)
{
        size_t cnt = 0;
        for (TriangleVector::const_iterator i = e.begin (); i != e.end (); ++i, ++cnt) {
                o << cnt << ". " << *i << " A=";

                if (i->A) {
                        o << *(i->A);
                }
                else {
                        o << "NULL";
                }

                o << " B=";

                if (i->B) {
                        o << *(i->B);
                }
                else {
                        o << "NULL";
                }

                o << " C=";

                if (i->C) {
                        o << *(i->C);
                }
                else {
                        o << "NULL";
                }

                o << "\n";
        }

        return o;
}


std::ostream &operator<< (std::ostream &o, TrianglePtrVector const &e)
{
        size_t cnt = 0;
        for (TrianglePtrVector::const_iterator i = e.begin (); i != e.end (); ++i, ++cnt) {
                o << **i;

                if (i + 1 != e.end ()) {
                        o << " | ";
                }
        }

        return o;
}

std::ostream &operator<< (std::ostream &o, TriangleIndex const &e)
{
        size_t cnt = 0;
        for (TriangleIndex::const_iterator i = e.begin (); i != e.end (); ++i, ++cnt) {
                TrianglePtrVector const &trianglesForPoint = *i;

                for (TrianglePtrVector::const_iterator k = trianglesForPoint.begin (); k != trianglesForPoint.end (); ++k) {
                        o << cnt << " : " << **k;

                        if (k + 1 != trianglesForPoint.end ()) {
                                o << " | ";
                        }
                }

                o << "\n";
        }

        return o;
}
#endif
#endif

} // namespace

#endif /* DELAUNAYINDEX_H_ */
