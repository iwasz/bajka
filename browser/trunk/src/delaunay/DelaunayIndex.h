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
#include <set>

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
        typedef std::list <TriangleEdgeType> TriangleEdgeList;
        typedef std::vector <TriangleType> TriangleVector;
        typedef std::vector <TriangleType const *> TrianglePtrVector; // TODO Data structure not optimized. Maybe some contiguous memory region can be used to eliminate memory partition and std::vector overhead.
        typedef std::vector <TrianglePtrVector> TriangleIndex;
        typedef boost::tuple <int, SideEnum, SideEnum> IntersectionInfo;

        DelaunayIndex (Input const &i) : input (i)
        {
                triangleIndex.resize (input.size ());
                edgeIndex.resize (input.size ());

                // TODO ***KRYTYCZNE*** ustawić tu tyle ile ma być. Da się to wyliczyć na początku!?
                std::cerr << input.size () << std::endl;
                triangulation.reserve (input.size () * 10);
        }

        TriangleVector const &getTriangulation () const { return triangulation; }
        size_t getNumTriangles () const { return triangulation.size (); }
        void addTriangle (IndexType index, TriangleType const *triangle);
        void addTriangle (TriangleType const &triangle);
        TriangleType const &getTriangle (size_t i) const { return triangulation.at (i); }
        TriangleType &getTriangle (size_t i) { return triangulation.at (i); }

        size_t getTriangleIndexSize () const { return triangleIndex.size (); }
        TrianglePtrVector const &getTrianglesForIndex (IndexType i) const { return triangleIndex[i]; }
        TrianglePtrVector &getTrianglesForIndex (IndexType i) { return triangleIndex[i]; }
        void clean ();

        void setVertex (TriangleType &t, SideEnum s, IndexType v);

/****************************************************************************/

        TriangleType *getAdjacentTriangle (TriangleType const &triangle, SideEnum side);
        void setAdjacentTriangle (TriangleType &t, SideEnum s, TriangleType *a);

        /**
         * Input : this->triangulation (performed earlier), edge to check for. Edge must have endpoints
         * in this->input.
         * Output : list of edges which intersects with edge.
         */
        void findCrossingEdges (TriangleEdgeType const &edge, TriangleEdgeList *crossingEdges, TrianglePtrVector *crossingTriangles) const;

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
        bool twoTrianglesConvex (TriangleEdgeType const &e/*, TriangleType const &a, TriangleType const &b*/) const;
        bool twoTrianglesNotDelaunay (TriangleEdgeType const &e) const;

        /**
         * Based on Cline and Renka
         */
        bool pointInCircumcircle (TriangleType const &triangle, IndexType point) const;

        /**
         * Perform a flip, and return new diagonal. Triangle index.
         */
        void flip (TriangleEdgeType const &oldDiagonal, TriangleEdgeType *newDiagonal);

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
        void getTriaglesForEdge (TriangleEdgeType const &e, TriangleType **a, TriangleType **b) const;

        /*
         *
         */
        void sortEdgeIndex ();

private:

        struct PartEdge {
                PartEdge (IndexType b_ = 0, TriangleType const *t_ = 0) : vertex (b_), triangle (t_) {}
                IndexType vertex;
                TriangleType const *triangle;
        };

        struct PartEdgeCompare {
                PartEdgeCompare () : a (0) {}

                bool operator () (PartEdge const &e1, PartEdge const &e2) const
                {
//                        std::cerr << a << ", " << e1.triangle << "," << e2.triangle << std::endl;

                        SideEnum c1Side = otherThan (getVertexSide (*e1.triangle, a), getVertexSide (*e1.triangle, e1.vertex));
                        IndexType c1 = getVertex (*e1.triangle, c1Side);

                        SideEnum c2Side = otherThan (getVertexSide (*e2.triangle, a), getVertexSide (*e2.triangle, e2.vertex));
                        IndexType c2 = getVertex (*e2.triangle, c2Side);

//                        std::cerr << a << ", " << *e1.triangle << ", " << *e2.triangle << ", " << e1.vertex << ", " <<  e2.vertex << "|" << c1 << ", " << c2 << "=" << ((e1.vertex < e2.vertex) && (c1 < c2)) << std::endl;

                        if (e1.vertex == e2.vertex) {
                                return c1 < c2;
                        }

                        return (e1.vertex < e2.vertex);
                }

                IndexType a;
        };

        /*
         * http://www.lafstern.org/matt/col1.pdf : Why you shouldn't use set (and what you should use instead) by Matt Austern
         */
        typedef std::vector <PartEdge> PartEdgeVector;
        typedef std::vector <PartEdgeVector> PartEdgeIndex;

        struct TraingleRemovePredicate {
                bool operator () (TriangleType const &t) { return !a (t) && !b (t) && !c (t); }
        };

        void addPartEdge (IndexType a, IndexType b, TriangleType const *t);

private:

        Input const &input;
        TriangleIndex triangleIndex;
        PartEdgeIndex edgeIndex;
        TriangleVector triangulation;

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
void DelaunayIndex<Input, Traits>::findCrossingEdges (TriangleEdgeType const &edge, TriangleEdgeList *crossingEdges, TrianglePtrVector *crossingTriangles) const
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
//                CrossingEdge crossingEdge;
//                crossingEdge.template get<0> () = commonEdge;
//                crossingEdge.template get<1> () = next;
                // TODO - rozwiązać sprawę z const / nie cost.
                next = const_cast <DelaunayIndex *> (this)->getAdjacentTriangle (*next, commonEdgeNumber);
//                crossingEdge.template get<2> () = next;
                commonEdgeNumber = getEdgeSide (*next, commonEdge);

                // Musi być, bo gdyby nie było, to by znaczyło, że constraint wychodzi poza zbiór punktów (ma jeden koniec gdzieś w powietrzu).
                assert (next);

                if (crossingTriangles) {
//                        crossingEdges->push_back (crossingEdge);
                        crossingEdges->push_back (commonEdge);
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
bool DelaunayIndex<Input, Traits>::twoTrianglesConvex (TriangleEdgeType const &firstDiagonal/*, TriangleType const &a, TriangleType const &b*/) const
{
        TriangleType *a = NULL;
        TriangleType *b = NULL;
        getTriaglesForEdge (firstDiagonal, &a, &b);
        assert (a && b);

        SideEnum aSide = getEdgeSide (*a, firstDiagonal);
        SideEnum bSide = getEdgeSide (*b, firstDiagonal);

        TriangleEdgeType secondDiagonal = TriangleEdgeType (getVertex (*a, aSide), getVertex (*b, bSide));
        EdgeType e1 = triangleEdgeToEdge (firstDiagonal);
        EdgeType e2 = triangleEdgeToEdge (secondDiagonal);
        return Delaunay::intersects (e1, e2);
}

/****************************************************************************/

template <typename Input, typename Traits>
bool DelaunayIndex<Input, Traits>::pointInCircumcircle (TriangleType const &triangle, IndexType point) const
{
        PointType const &ta = input[a (triangle)];
        PointType const &tb = input[b (triangle)];
        PointType const &tc = input[c (triangle)];
        PointType const &tp = input[point];

        double cosa = (ta.x - tc.x) * (tb.x - tc.x) + (ta.y - tc.y) * (tb.y - tc.y);
        double cosb = (tb.x - tp.x) * (ta.x - tp.x) + (tb.y - tp.y) * (ta.y - tp.y);

        if (cosa >= 0 && cosb >= 0) {
                return false;
        }

        if (cosa < 0 && cosb < 0) {
                return true;
        }

        double sinab = ((ta.x - tc.x) * (tb.y - tc.y) - (tb.x - tc.x) * (ta.y - tc.y)) * cosb + ((tb.x - tp.x) * (ta.y - tp.y) - (ta.x - tp.x) * (tb.y - tp.y)) * cosa;

        if (sinab < 0) {
                return true;
        }

        return false;
}

/****************************************************************************/

template <typename Input, typename Traits>
bool DelaunayIndex<Input, Traits>::twoTrianglesNotDelaunay (TriangleEdgeType const &firstDiagonal) const
{
        TriangleType *a = NULL;
        TriangleType *b = NULL;
        getTriaglesForEdge (firstDiagonal, &a, &b);

        SideEnum aSide = getEdgeSide (*a, firstDiagonal);
        SideEnum bSide = getEdgeSide (*b, firstDiagonal);

        return pointInCircumcircle (*a, getVertex (*b, bSide)) || pointInCircumcircle (*b, getVertex (*a, aSide));
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
void DelaunayIndex<Input, Traits>::addPartEdge (IndexType i1, IndexType i2, TriangleType const *t)
{
        assert (edgeIndex.size () > i1);
//        std::cerr << i1 << ", " << edgeIndex[i1].size () << ", " << edgeIndex[i1].capacity () << ", " <<  t << std::endl;
//        edgeIndex[i1].reserve (100);
        edgeIndex[i1].push_back (PartEdge (i2, t));
}

/****************************************************************************/

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::addTriangle (TriangleType const &triangle)
{
        triangulation.push_back (triangle);

        // Update triangle index.
        TriangleType const *t = &triangulation.back ();
//        std::cerr << triangulation.size () << ", " << triangle << ", " << t << std::endl;

        addTriangle (a (*t), t);
        addTriangle (b (*t), t);
        addTriangle (c (*t), t);

        addPartEdge (a (*t), b (*t), t);
        addPartEdge (b (*t), c (*t), t);
        addPartEdge (c (*t), a (*t), t);

        addPartEdge (b (*t), a (*t), t);
        addPartEdge (c (*t), b (*t), t);
        addPartEdge (a (*t), c (*t), t);
}

/****************************************************************************/

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::sortEdgeIndex ()
{
        PartEdgeCompare comparator;
        for (typename PartEdgeIndex::iterator i = edgeIndex.begin (); i != edgeIndex.end (); ++i, ++comparator.a) {
                PartEdgeVector &edgesForIndex = *i;
                std::cerr << "----" << edgesForIndex.size() << std::endl;
                assert (edgesForIndex.size () > 1);
                std::sort (edgesForIndex.begin (), edgesForIndex.end (), comparator);
                PartEdge &e1 = edgesForIndex[0];
                PartEdge &e2 = edgesForIndex[1];

//                std::cerr << "-------------" << std::endl;

                if (e1.vertex == e2.vertex) {
                        std::swap (e1, e2);
                }
        }

        std::cerr << "--------TRIANGLE INDEX--------" << std::endl;
        std::cerr << triangleIndex << std::endl;
        std::cerr << "--------EDGE INDEX--------" << std::endl;

        int cnt = 0;
        for (typename PartEdgeIndex::const_iterator i = edgeIndex.begin (); i != edgeIndex.end (); ++i, ++cnt) {
                PartEdgeVector const &edgesForIndex = *i;

                std::cerr << cnt << ". ";

                for (typename PartEdgeVector::const_iterator j = edgesForIndex.begin (); j != edgesForIndex.end (); ++j) {
                        PartEdge const &edge = *j;
                        std::cerr << edge.vertex << ":" << *edge.triangle << " | ";
                }

                std::cerr << std::endl;
        }
}

/****************************************************************************/

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::flip (TriangleEdgeType const &oldDiagonal, TriangleEdgeType *newDiagonal)
{
        TriangleType *f = 0;
        TriangleType *s = 0;
        getTriaglesForEdge (oldDiagonal, &f, &s);

#if 0
        std::cerr << "oldDiagonal : " << oldDiagonal << ", f : ";
        if (f) { std::cerr << *f; } else { std::cerr << "NULL"; }
        std::cerr << ", s : ";
        if (s) { std::cerr << *s; } else { std::cerr << "NULL"; }
        std::cerr << ", ptr : " << f << ", " << s << std::endl;
#endif

        if (!s) {
                *newDiagonal = oldDiagonal;
                std::cerr << "!s - return" << std::endl;
                return;
        }

        SideEnum foa = getVertexSide (*f, oldDiagonal.a);
        SideEnum fob = getVertexSide (*f, oldDiagonal.b);
        SideEnum fc = otherThan (foa, fob);
        IndexType fcIndex = getVertex (*f, fc);
#if 0
        std::cerr << "foa : " << (int)foa << ", fob : " << (int)fob << ", fc : " << (int)fc << ", fcIndex : " << fcIndex << std::endl;
#endif
        SideEnum soa = getVertexSide (*s, oldDiagonal.b);
        SideEnum sob = getVertexSide (*s, oldDiagonal.a);
        SideEnum sc = otherThan (soa, sob);
        IndexType scIndex = getVertex (*s, sc);
#if 0
        std::cerr << "soa : " << (int)soa << ", sob : " << (int)sob << ", sc : " << (int)sc << ", scIndex : " << scIndex << std::endl;
#endif
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
#if 0
        std::cerr << "newDiagonal : " << *newDiagonal << ", f : " << *f << ", s : " << *s << std::endl;
#endif
}

/****************************************************************************/

/*
 * TODO nieoptymalnie - on iteruje za każdym razem po wszystkich trójkątach przyległych to e.a i
 * szuka w nich e.b. Możnaby jakiś index, albo żeby triangleIndex zawierał jakąś strukturę, którą
 * można przeszukiwać.
 */
template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::getTriaglesForEdge (TriangleEdgeType const &e, TriangleType **a, TriangleType **b) const
{
        TrianglePtrVector const &triaglesA = triangleIndex[e.a];
        *a = *b = 0;
#if 0
        std::cerr << "Edge : " << e << std::endl;
#endif
        for (typename TrianglePtrVector::const_iterator i = triaglesA.begin (); i != triaglesA.end (); ++i) {
                Triangle const *t = *i;
#if 0
                std::cerr << "getTrForE : " << *t;
#endif
                SideEnum s = getVertexSide (*t, e.a);
                TriangleEdgeType me = getEdge (*t, s);

                if (me.a == e.b || me.b == e.b) {
                        if (!*a) {
                                // TODO get rid od cast
                                *a = const_cast <TriangleType *> (t);
#if 0
                                std::cerr << " +++a";
#endif
                        }
                        else if (!*b) {
                                *b = const_cast <TriangleType *> (t);
#if 0
                                std::cerr << " +++b"  << std::endl;
#endif
                                return;
                        }
                }

#if 0
                std::cerr  << std::endl;
#endif
        }
}

/****************************************************************************/

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::setVertex (TriangleType &t, SideEnum s, IndexType v)
{
        IndexType current = Delaunay::getVertex (t, s);
        TrianglePtrVector &triangles = triangleIndex[current];
        triangles.erase (std::remove (triangles.begin (), triangles.end (), &t), triangles.end ());

        Delaunay::setVertex (t, s, v);
        TrianglePtrVector &trianglesV = triangleIndex[v];
        trianglesV.push_back (&t);
}

/****************************************************************************/

template <typename Input, typename Traits>
void DelaunayIndex<Input, Traits>::clean ()
{
        triangulation.erase (std::remove_if (triangulation.begin (), triangulation.end (), TraingleRemovePredicate ()), triangulation.end ());
}

/****************************************************************************/

#ifndef NDEBUG
std::ostream &operator<< (std::ostream &o, std::vector <Triangle> const &e)
{
        typedef std::vector <Triangle> TriangleVector;

        size_t cnt = 0;
        for (typename TriangleVector::const_iterator i = e.begin (); i != e.end (); ++i, ++cnt) {
                o << cnt << ". " << *i << " A=";

                if (i->tA) {
                        o << *(i->tA);
                }
                else {
                        o << "NULL";
                }

                o << " B=";

                if (i->tB) {
                        o << *(i->tB);
                }
                else {
                        o << "NULL";
                }

                o << " C=";

                if (i->tC) {
                        o << *(i->tC);
                }
                else {
                        o << "NULL";
                }

                o << "\n";
        }

        return o;
}

std::ostream &operator<< (std::ostream &o, std::vector <Triangle const *> const &e)
{
        size_t cnt = 0;
        for (std::vector <Triangle const *>::const_iterator i = e.begin (); i != e.end (); ++i, ++cnt) {
                o << **i;

                if (i + 1 != e.end ()) {
                        o << " | ";
                }
        }

        return o;
}

std::ostream &operator<< (std::ostream &o, std::vector <std::vector <Triangle const *> > const &e)
{
        typedef std::vector <Triangle const *> TrianglePtrVector;
        typedef std::vector <TrianglePtrVector> TriangleIndex;

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

} // namespace

#endif /* DELAUNAYINDEX_H_ */
