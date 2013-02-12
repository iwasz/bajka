/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DELAUNAYTRIANGULATION_H_
#define DELAUNAYTRIANGULATION_H_

#include "DelaunayTypes.h"
#include "DelaunayIndex.h"
#include "DelaunayTriangle.h"

#include <boost/polygon/voronoi.hpp>
#include <boost/math/special_functions/round.hpp>
#ifndef NDEBUG
#include <boost/timer/timer.hpp>
#endif

//#include <geometry/Ring.h>
//#include <model/static/Ring.h>
//#include "geometry/Point.h"
//#include "TestView.h"
//#include <stdint.h>

namespace boost {
namespace polygon {

template <>
struct geometry_concept<Geometry::Point> {
        typedef point_concept type;
};

template<>
struct point_traits<Geometry::Point> {
        typedef int coordinate_type;

        /*
         * TODO sprawdzić jak często to się wykonuje i skąd. Jak tylko w kroku inicjacji, to OK.
         * Dał bym tutaj też mnożnik, żeby uniknąć sytuacji, kiedy dwa zmiennoprzecinkowe punkty
         * wejściowe, które są bardzo blisko siebie zostaną przez poniższy get zwróceone jako
         * ten sam punkt. Można albo mnożyć przez stała (np 1000), albo znaleźć najmniejszą różnicę
         * mięczy dwoma współrzednymi w danych wejściowych i przeskalować je odpowiednio.
         */
        static inline coordinate_type get (const Geometry::Point& point, orientation_2d orient)
        {
                return (orient == HORIZONTAL) ? boost::math::iround (point.x) : boost::math::iround (point.y);
        }
};

}
}

/**
 *
 */
template<typename T>
struct my_voronoi_diagram_traits {
        typedef T coordinate_type;
        typedef boost::polygon::voronoi_cell<coordinate_type> cell_type;
        typedef boost::polygon::voronoi_vertex<coordinate_type> vertex_type;
        typedef boost::polygon::voronoi_edge<coordinate_type> edge_type;

        // This copes with degenerations.
        typedef struct {
                bool operator() (const vertex_type& v1, const vertex_type& v2) const
                {
                        return false;
                }
        } vertex_equality_predicate_type;
};

/**
 *
 */
typedef boost::polygon::voronoi_diagram<double, my_voronoi_diagram_traits <double> > my_voronoi_diagram;

/*##########################################################################*/

//// size_t może być zamienione na uint32_t (24 bytes on 32bit machine, 48 or 36 on 64bit).
//struct Triangle {
//
//        Triangle () : a (0), b (0), c (0), A (0), B (0), C (0) {}
//
//        // Endpoints of a triangle.
//        uint32_t a, b, c;
//
//        // Adjacent triangles (opposite side of a, b, c).
//        Triangle *A, *B, *C;
//
//        bool hasPoint (uint32_t p) const { return p == a || p == b || p == c; }
//        bool hasEdge (uint32_t x, uint32_t y) const { return hasPoint (x) && hasPoint(y); }
//};

//BOOST_STATIC_ASSERT (boost::has_trivial_assign <Triangle>::value);
//BOOST_STATIC_ASSERT (boost::has_trivial_copy <Triangle>::value);
//BOOST_STATIC_ASSERT (boost::is_pod <Triangle>::value);

//Triangle makeTriangle (uint32_t a, uint32_t b, uint32_t c)
//{
//        Triangle t;
//        t.a = a;
//        t.b = b;
//        t.c = c;
//        return t;
//}


//std::ostream &operator<< (std::ostream &o, Triangle const &i)
//{
//        o << i.a << "," << i.b << "," << i.c;
//        return o;
//}

//std::ostream &operator<< (std::ostream &o, TriangleVector const &e)
//{
//        size_t cnt = 0;
//        for (TriangleVector::const_iterator i = e.begin (); i != e.end (); ++i, ++cnt) {
//                o << cnt << ". " << *i << " A=";
//
//                if (i->A) {
//                        o << *(i->A);
//                }
//                else {
//                        o << "NULL";
//                }
//
//                o << " B=";
//
//                if (i->B) {
//                        o << *(i->B);
//                }
//                else {
//                        o << "NULL";
//                }
//
//                o << " C=";
//
//                if (i->C) {
//                        o << *(i->C);
//                }
//                else {
//                        o << "NULL";
//                }
//
//                o << "\n";
//        }
//
//        return o;
//}


//std::ostream &operator<< (std::ostream &o, TrianglePtrVector const &e)
//{
//        size_t cnt = 0;
//        for (TrianglePtrVector::const_iterator i = e.begin (); i != e.end (); ++i, ++cnt) {
//                o << **i;
//
//                if (i + 1 != e.end ()) {
//                        o << " | ";
//                }
//        }
//
//        return o;
//}

//std::ostream &operator<< (std::ostream &o, TriangleIndex const &e)
//{
//        size_t cnt = 0;
//        for (TriangleIndex::const_iterator i = e.begin (); i != e.end (); ++i, ++cnt) {
//                TrianglePtrVector const &trianglesForPoint = *i;
//
//                for (TrianglePtrVector::const_iterator k = trianglesForPoint.begin (); k != trianglesForPoint.end (); ++k) {
//                        o << cnt << " : " << **k;
//
//                        if (k + 1 != trianglesForPoint.end ()) {
//                                o << " | ";
//                        }
//                }
//
//                o << "\n";
//        }
//
//        return o;
//}

/****************************************************************************/

namespace Geometry {
struct Edge {
        Geometry::Point a;
        Geometry::Point b;
};

BOOST_STATIC_ASSERT (boost::has_trivial_assign <Edge>::value);
BOOST_STATIC_ASSERT (boost::has_trivial_copy <Edge>::value);
BOOST_STATIC_ASSERT (boost::is_pod <Edge>::value);

float getArea (Point const &a, Point const &b, Point const &c)
{
        return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

bool isLeft (Point const &a, Point const &b, Point const &c)
{
        return getArea (a, b, c) > 0;
}

// TODO To musi pracować na INTACH z voronoia! Nie może być tego epsilona!
bool isCollinear (Point const &a, Point const &b, Point const &c)
{
        return fabs (getArea (a, b, c)) < 0.00001;
}

/**
 * Computational geometry in C - second edition.
 */
bool intersects (Edge const &a, Edge const &b)
{
        if (isCollinear (a.a, a.b, b.a) ||
            isCollinear (a.a, a.b, b.b) ||
            isCollinear (b.a, b.b, a.a) ||
            isCollinear (b.a, b.b, a.b)) {
                return false;
        }

        return (isLeft (a.a, a.b, b.a) ^ isLeft (a.a, a.b, b.b)) && (isLeft (b.a, b.b, a.a) ^ isLeft (b.a, b.b, a.b));
}

}
/*##########################################################################*/

namespace Delaunay {

/**
 * Input must be in COUNTER CLOCKWISE order.
 */
template <typename Input, typename Traits = DelaunayTriangulationTraits<> >
class DelaunayTriangulation {
public:

        DelaunayTriangulation (Input const &input) : index (input) {}
        void constructDelaunay ();

        // TODO do usunięcia lub przeniesienia.
        typedef double coordinate_type;
        typedef my_voronoi_diagram::vertex_type vertex_type;
        typedef my_voronoi_diagram::edge_type edge_type;
        typedef my_voronoi_diagram::cell_type cell_type;
        typedef Geometry::Point point_type;
        typedef std::pair <uint32_t, uint32_t> Edge;
        typedef std::list <Edge> EdgeList;
        typedef boost::tuple <Edge, Triangle const *, Triangle const *> CrossingEdge;
        typedef std::list <CrossingEdge> CrossingEdgeList;

private:

        Input const &input;
        DelaunayIndex <Input, Traits> index;

//        Geometry::LineString *voronoi;
//        Geometry::LineString *delaunay;
//        Geometry::LineString *crossing;

};

/****************************************************************************/

//std::ostream &operator<< (std::ostream &o, DelaunayTriangulation::Edge const &e)
//{
//        o << "(" << e.first << "," << e.second << ")";
//        return o;
//}

/****************************************************************************/

template <typename Input, typename Traits>
void DelaunayTriangulation<Input, Traits>::constructDelaunay ()
{
        my_voronoi_diagram vd;

#ifndef NDEBUG
        boost::timer::cpu_timer t0;
#endif

        construct_voronoi (input.begin (), input.end (), &vd);

#ifndef NDEBUG
        printlog ("Voronoi diagram construction time : %f ms", t0.elapsed ().wall / 1000000.0);
#endif

        boost::timer::cpu_timer t1;

        // 1. Make triangles from voronoi.
        for (my_voronoi_diagram::const_vertex_iterator it = vd.vertices ().begin (); it != vd.vertices ().end (); ++it) {
                vertex_type const &vertex = *it;
                edge_type const *edge = vertex.incident_edge ();

                uint32_t triangleVertices[3];
                uint32_t triangleCnt = triangulation.size ();
                vertex.color (triangleCnt);

                size_t edgeCnt = 0;
                do {
                        if (!edge->is_primary ()) {
                                continue;
                        }

                        cell_type const *cell = edge->cell ();
                        size_t index = cell->source_index ();
                        triangleVertices[edgeCnt++] = index;
                        // Add 1 thus default 0 is invalid.
                        edge->color (triangleCnt + 1);
                        edge = edge->rot_next ();
                } while (edge != vertex.incident_edge () && edgeCnt < 3);

                if (edgeCnt == 3) {
                        Triangle triangle;
                        triangle.a = triangleVertices[0];
                        triangle.b = triangleVertices[1];
                        triangle.c = triangleVertices[2];
                        triangulation.push_back (triangle);
//                        std::cerr << triangulation << std::endl;

                        // Update triangle index.
                        Triangle const *t = &triangulation.back ();

                        assert (triangleIndex.size () > triangle.a);
                        triangleIndex[triangle.a].push_back (t);

                        assert (triangleIndex.size () > triangle.b);
                        triangleIndex[triangle.b].push_back (t);

                        assert (triangleIndex.size () > triangle.c);
                        triangleIndex[triangle.c].push_back (t);

//                        std::cerr << "Point " << triangle.a << " has incident triangle : " << *t << std::endl;
//                        std::cerr << "Point " << triangle.b << " has incident triangle : " << *t << std::endl;
//                        std::cerr << "Point " << triangle.c << " has incident triangle : " << *t << std::endl;
                }
        }

#ifndef NDEBUG
//        std::cerr << "Delaunay triangulation produced : " << triangulation.size () << " triangles." << std::endl;
#endif

        // 2. Link triangles.
        for (my_voronoi_diagram::const_vertex_iterator it = vd.vertices ().begin (); it != vd.vertices ().end (); ++it) {
                vertex_type const &vertex = *it;
                Triangle &triangle = triangulation[vertex.color ()];
                edge_type const *edge = vertex.incident_edge ();
                size_t edgeCnt = 0;

                do {
                        if (!edge->is_primary ()) {
                                continue;
                        }

                        uint32_t adjacentIndex = edge->twin ()->color ();

                        // Index with value 0 is invalid.
                        if (!adjacentIndex) {
                                edge = edge->rot_next ();
                                continue;
                        }

                        Triangle &adjacentTriangle = triangulation[adjacentIndex - 1];

                        // Sprawdzić którym bokiem się stykają i ustawić.
                        if (!adjacentTriangle.hasPoint (triangle.a)) {
                                triangle.A = &adjacentTriangle;
                        }
                        else if (!adjacentTriangle.hasPoint (triangle.b)) {
                                triangle.B = &adjacentTriangle;
                        }
                        else if (!adjacentTriangle.hasPoint (triangle.c)) {
                                triangle.C = &adjacentTriangle;
                        }

                        ++edgeCnt;
                        edge = edge->rot_next ();
                } while (edge != vertex.incident_edge () && edgeCnt < 3);
        }

#if 0
        std::cout << triangulation << std::endl;
#endif

        // 3. Update triangleVector (data structure for CDT).
        /*
         * TODO This is loop made for simple polygons (without holes). It is also possible to make
         * loop for dicrete list of constraints (that are not linked).
         */
        EdgeList missingConstraints;
        size_t inputSize = input.size ();

        for (size_t i = 0; i < inputSize; ++i) {
                size_t j = (i + 1) % inputSize;

                assert (triangleIndex.size () > i);
                TrianglePtrVector const &trianglesForPoint = triangleIndex[i];

#if 0
                if (trianglesForPoint.empty ()) {
                        std::cerr << "UWAGA : trianglesForPoint.empty () : nie ma trójkątów stycznych do punktu o indeksie : " << i << ". TODO rozkminić czy to OK. i_max = " << inputSize -1  << std::endl;
                }
#endif

                assert (!trianglesForPoint.empty ());

                bool found = false;
                for (TrianglePtrVector::const_iterator k = trianglesForPoint.begin (); k != trianglesForPoint.end (); ++k) {
                        if ((*k)->hasEdge (i, j)) {
                                found = true;
                                break;
                        }
                }

                if (!found) {
#if 1
                        std::cerr << "Constraint (" << i << ", " << j << ") was **NOT** found in triangulation." << std::endl;
#endif
                        missingConstraints.push_back (std::make_pair (i, j));
                }
        }

        // 4. Add missing segments.
        for (EdgeList::const_iterator i = missingConstraints.begin (); i != missingConstraints.end (); ++i) {
                Edge const &missingConstraint = *i;

                CrossingEdgeList crossingEdges;
                TrianglePtrVector crossingTriangles;

                findCrossingEdges (missingConstraint, &crossingEdges, &crossingTriangles);

//                std::cerr << "Constraint " << missingConstraint << " crosses : " << crossingTriangles << std::endl;

                for (TrianglePtrVector::const_iterator i = crossingTriangles.begin (); i != crossingTriangles.end (); ++i) {
                        crossing->push_back (input[(*i)->a]);
                        crossing->push_back (input[(*i)->b]);
                        crossing->push_back (input[(*i)->c]);
                }

                EdgeList newEdges;
                CrossingEdgeList::iterator i = crossingEdges.begin ();
                while (!crossingEdges.empty ()) {
                        CrossingEdgeList::iterator next = i;
                        ++next;

                        CrossingEdge e = *i;

                        if (!twoTrianglesConvex (e)) {

                                std::cerr << "####> !CONVEX" << std::endl;
                                if (crossingEdges.size () == 1) {
                                        /*
                                         * TODO Jeśli jest tylko jedna przecinająca dany constraint, to jeśli convex,
                                         * to flip, a jeśli nie, to nie wiem, ale coś trzeba tu zrobić.
                                         */
                                }

                                i = next;
                                continue;
                        }

                        std::cerr << "####> +++CONVEX" << std::endl;

                        // Dwa przyległę trójkąty zawierające e tworzą czworobok wypukły.
                        crossingEdges.erase (i);
                        Edge newDiagonal;
                        /*
                         * Tu trzeba
                         * - uaktualnić wierzchołki trójkątów.
                         * - uaktualnić ich zlinkowane trójkąty.
                         * - uaktualnic triangleIndex (potrzebny w findCrossing edges).
                         */
//                        flip (a, b, &newDiagonal);
//
//                        if (intersects (e.get<0> (), newDiagonal)) {
//                                missingConstraints.push_back (newDiagonal);
//                        }
//                        else {
//                                newEdges.push_back (newDiagonal);
//                        }

                        i = next;
                }
        }

        // 4. Make CDT from DT.


        // 5. Create debug output
//        Trójkąty
//        for (TriangleVector::const_iterator i = triangulation.begin (); i != triangulation.end (); ++i) {
//                delaunay->push_back (input[i->a]);
//                delaunay->push_back (input[i->b]);
//                delaunay->push_back (input[i->c]);
//        }

//        Krawedzie trójkątów
        for (TriangleVector::const_iterator i = triangulation.begin (); i != triangulation.end (); ++i) {
                delaunay->push_back (input[i->a]);
                delaunay->push_back (input[i->b]);
                delaunay->push_back (input[i->b]);
                delaunay->push_back (input[i->c]);
                delaunay->push_back (input[i->c]);
                delaunay->push_back (input[i->a]);
        }

#ifndef NDEBUG
        printlog ("Triangulation time (derived from voronoi as its dual) : %f ms", t1.elapsed ().wall / 1000000.0);
        //        printlog ("Voronoi prim. edges : %d", result);
//        std::cout << triangulation << std::endl;
#endif
}

} // namespace

#endif /* DELAUNAYTRIANGULATION_H_ */
