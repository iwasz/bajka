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

// size_t może być zamienione na uint32_t (24 bytes on 32bit machine, 48 or 36 on 64bit).
struct Triangle {

        Triangle () : a (0), b (0), c (0), A (0), B (0), C (0) {}

        // Endpoints of a triangle.
        uint32_t a, b, c;

        // Adjacent triangles (opposite side of a, b, c).
        Triangle *A, *B, *C;

        bool hasPoint (uint32_t p) const { return p == a || p == b || p == c; }
        bool hasEdge (uint32_t x, uint32_t y) const { return hasPoint (x) && hasPoint(y); }
};

//BOOST_STATIC_ASSERT (boost::has_trivial_assign <Triangle>::value);
//BOOST_STATIC_ASSERT (boost::has_trivial_copy <Triangle>::value);
//BOOST_STATIC_ASSERT (boost::is_pod <Triangle>::value);

Triangle makeTriangle (uint32_t a, uint32_t b, uint32_t c)
{
        Triangle t;
        t.a = a;
        t.b = b;
        t.c = c;
        return t;
}

typedef std::vector <Triangle> TriangleVector;

std::ostream &operator<< (std::ostream &o, Triangle const &i)
{
        o << i.a << "," << i.b << "," << i.c;
        return o;
}

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

// Data structure not optimized. Maybe some contiguous memory region can be used to eliminate memory partition and std::vector overhead.
typedef std::vector <Triangle const *> TrianglePtrVector;

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

typedef std::vector <TrianglePtrVector> TriangleIndex;

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

typedef std::vector <std::vector <uint32_t> > EdgeFans;

std::ostream &operator<< (std::ostream &o, EdgeFans const &e)
{
        size_t cnt = 0;
        for (EdgeFans::const_iterator i = e.begin (); i != e.end (); ++i, ++cnt) {
                o << cnt << " : ";

                for (std::vector <uint32_t>::const_iterator j = i->begin (); j != i->end (); ++j) {
                        o << *j;

                        if (j + 1 == i->end ()) {
                                o << "\n";
                                break;
                        }
                        else {
                                o << ", ";
                        }
                }
        }

        return o;
}

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

template <typename I>
struct DelaunayTriangulationTraits {
        typedef I IndexType;
};

/**
 * Input must be in COUNTER CLOCKWISE order.
 */
uyhhhhhhhhhhhhhclass DelaunayTriangulation {
public:

        DelaunayTriangulation (const Geometry::Ring& i, Geometry::LineString* v, Geometry::LineString* d, Geometry::LineString* c) :
                        input(i), voronoi(v), delaunay(d), crossing (c)
        {
                triangleIndex.resize (input.size ());
                // TODO ***KRYTYCZNE*** ustawić tu tyle ile ma być. Da się to wyliczyć na początku!?
                triangulation.reserve (input.size () * 10);
        }

        void constructDelaunay ();
//        void constructDelaunay2 ();
        void constructDelaunay3 ();

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
        /**
         * Returns if diagonal (a, b) lays completely inside the polygon. It assumes two things:
         * - Points in polygon are stored in counter clockwise order.
         * - Checked diagonal do not intersects with boundary segments (defined by polygon itself)
         * in points other than a and b.
         * This second condition is easy to conform to, since we operate on diagonals generated
         * by triangulation algotihm.
         */
        bool diagonalInside (const Geometry::Point& a,
                        const Geometry::Point& ap, const Geometry::Point& an,
                        const Geometry::Point& b) const;

        void clipInfiniteEdge (const edge_type& edge, std::vector<point_type>* clipped_edge) const;

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
        const Geometry::Ring &input;
        Geometry::LineString *voronoi;
        Geometry::LineString *delaunay;
        Geometry::LineString *crossing;
        TriangleVector triangulation;
        TriangleIndex triangleIndex;
};

/****************************************************************************/

std::ostream &operator<< (std::ostream &o, DelaunayTriangulation::Edge const &e)
{
        o << "(" << e.first << "," << e.second << ")";
        return o;
}

/****************************************************************************/

boost::tuple <int, int, int> DelaunayTriangulation::intersects (Triangle const &t, Geometry::Edge const &e) const
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

void DelaunayTriangulation::constructDelaunay ()
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

        int result = 0;
        for (my_voronoi_diagram::const_edge_iterator it = vd.edges ().begin (); it != vd.edges ().end (); ++it) {
                if (it->is_primary ()) {

                        ++result;

                        my_voronoi_diagram::vertex_type const *v0 = it->vertex0 ();
                        my_voronoi_diagram::vertex_type const *v1 = it->vertex1 ();

#if 0
                        my_voronoi_diagram::edge_type const &edge = *it;
                        my_voronoi_diagram::edge_type const *twin = edge.twin ();

                        my_voronoi_diagram::cell_type const *cell = edge.cell ();
                        my_voronoi_diagram::cell_type const *nextCell = twin->cell ();

                        /*
                         * Konstruuj GRAF delaunay - w wyniku mogą pojawić wielokaty większe niż trójkąty jeżeli w poblizuu siebie
                         * znajdą się więcej niż 3 cocircullar sites.
                         */
                        if (cell->contains_point () && nextCell->contains_point ()) {
                                // Start point of delaunay edge to be drawn.
                                std::size_t indexA = cell->source_index ();
                                Geometry::Point const &a = input[indexA];
                                Geometry::Point const &ap = input[(indexA == 0) ? (pointsSize - 1) : (indexA - 1)];
                                Geometry::Point const &an = input[(indexA == pointsSize - 1) ? (0) : (indexA + 1)];

                                // End point of delaunay edge to be drawn.
                                std::size_t indexB = nextCell->source_index ();
                                Geometry::Point const &b = input[indexB];

                                if (diagonalInside (a, ap, an, b)) {
                                        // TODO powtórzenia.
                                        delaunay->push_back (Geometry::makePoint (a.x, a.y));
                                        delaunay->push_back (Geometry::makePoint (b.x, b.y));
//                                        edges.push_back (std::make_pair (indexA, indexB));

                                        // TODO Tu jest spadek dokładności.
                                        uint32_t min = std::min (indexA, indexB);
                                        uint32_t max = std::max (indexA, indexB);

                                        edgeFans[min].push_back (max);
//                                        std::cerr << min << "->" << max << std::endl;
                                }
                        }
#endif
                        if (it->is_infinite ()) {
                                std::vector<point_type> samples;
                                clipInfiniteEdge (*it, &samples);
                                voronoi->push_back (samples[0]);
                                voronoi->push_back (samples[1]);
                        }
                        else {
                                voronoi->push_back (Geometry::makePoint (v0->x (), v0->y ()));
                                voronoi->push_back (Geometry::makePoint (v1->x (), v1->y ()));
                        }
                }
        }

#ifndef NDEBUG
        printlog ("Triangulation time (derived from voronoi as its dual) : %f ms", t1.elapsed ().wall / 1000000.0);
        printlog ("Voronoi prim. edges : %d", result);
//        std::cout << edgeFans << std::endl;
#endif
}

#if 0
void DelaunayTriangulation::addTriangle (uint32_t b, uint32_t c, size_t& a)
{
        uint32_t bcMin = std::min(b, c);
        uint32_t bcMax = std::max(b, c);
        const std::vector<uint32_t>& edgesOfbcMin = edgeFans[bcMin];
        // Znaleziono krawedz b-c
        if (std::find(edgesOfbcMin.begin(), edgesOfbcMin.end(), bcMax)
                        != edgesOfbcMin.end()) {
                triangulation.push_back(makeTriangle(a, b, c));
        }
}

/****************************************************************************/

void DelaunayTriangulation::constructDelaunay2 ()
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

        // 1. Store all the triangle edges in convenient format.
        for (my_voronoi_diagram::const_cell_iterator it = vd.cells ().begin (); it != vd.cells ().end (); ++it) {

                my_voronoi_diagram::cell_type const &cell = *it;

                if (cell.color () || !cell.contains_point ()) {
                        continue;
                }

                cell.color (true);
                my_voronoi_diagram::cell_type::source_index_type index = cell.source_index();
                my_voronoi_diagram::edge_type const *edge = cell.incident_edge ();

                do {
                        if (edge->color () || !edge->is_primary ()) {
                                edge = edge->next ();
                                continue;
                        }

                        edge->color (true);
                        edge->twin ()->color (true);

                        my_voronoi_diagram::cell_type const *adjacentCell = edge->twin ()->cell ();

                        if (!adjacentCell->contains_point ()) {
                                edge = edge->next ();
                                continue;
                        }

                        my_voronoi_diagram::cell_type::source_index_type indexAdjacent = adjacentCell->source_index();

                        // TODO Tu jest spadek dokładności (z 64bit -> 32bit).
                        uint32_t min = std::min (index, indexAdjacent);
                        uint32_t max = std::max (index, indexAdjacent);

                        edgeFans[min].push_back (max);
                        edge = edge->next ();
                } while (edge != cell.incident_edge ());
        }

#ifndef NDEBUG
        std::cout << edgeFans << std::endl;
#endif

        // 2. make triangles from data gathered in step 1.
        size_t a = 0;
        for (EdgeFans::const_iterator i = edgeFans.begin (); i != edgeFans.end (); ++i, ++a) {

                // TODO Czy napewno dobry warunek!?
                if (i->size () < 2) {
                        continue;
                }

                if (i->size () == 2) {
                        uint32_t b = i->operator [] (0);
                        uint32_t c = i->operator [] (1);
                        addTriangle (b, c, a);
                        continue;
                }

                // Tylko przy założeniu, ze pierwszy if jest dobry.
                for (std::vector <uint32_t>::const_iterator j = i->begin (); j != i->end (); ++j) {

                        // Prawdodobny trójkąt : a, b, c. krawędzie a-b i a-c zostały znalezione. Teraz trzeba odszukać czy istnieje b-c.
                        uint32_t b;

                        if (j == i->begin ()) {
                                b = *(i->end () - 1);
                        }
                        else {
                                b = *(j - 1);
                        }

                        uint32_t c = *j;
                        addTriangle (b, c, a);
                }
        }

        // 3. Create debug output
        for (TriangleVector::const_iterator i = triangulation.begin (); i != triangulation.end (); ++i) {
                delaunay->push_back (input[i->a]);
                delaunay->push_back (input[i->b]);
                delaunay->push_back (input[i->c]);
        }

#ifndef NDEBUG
        printlog ("Triangulation time (derived from voronoi as its dual) : %f ms", t1.elapsed ().wall / 1000000.0);
        //        printlog ("Voronoi prim. edges : %d", result);
//        std::cout << triangulation << std::endl;
#endif
}
#endif

/****************************************************************************/

void DelaunayTriangulation::constructDelaunay3 ()
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
        std::cerr << "Delaunay triangulation produced : " << triangulation.size () << " triangles." << std::endl;
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

                std::cerr << "Constraint " << missingConstraint << " crosses : " << crossingTriangles << std::endl;

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

/****************************************************************************/

Triangle *getAdjacentTriangle (Triangle const &triangle, int side)
{
        switch (side) {
        case 1:
                return triangle.A;
        case 2:
                return triangle.B;
        case 3:
                return triangle.C;
        case 0:
        default:
                return NULL;
        }
}

/****************************************************************************/

DelaunayTriangulation::Edge getTriangleEdge (Triangle const &t, int side)
{
        assert (side > 0 && side < 4);

        switch (side) {
        case 1:
                return std::make_pair (t.c, t.b);
        case 2:
                return std::make_pair (t.c, t.a);
        case 3:
                return std::make_pair (t.b, t.a);
        case 0:
        default:
                return DelaunayTriangulation::Edge ();
        }
}

/****************************************************************************/

uint32_t getTriangleVertex (Triangle const &t, int side)
{
        assert (side > 0 && side < 4);

        switch (side) {
        case 1:
                return t.a;
        case 2:
                return t.b;
        case 3:
                return t.c;
        case 0:
        default:
                return 0;
        }
}

/****************************************************************************/

int getEdgeSide (Triangle const &t, DelaunayTriangulation::Edge const &e)
{
        return 6 - (((e.first == t.a) | ((e.first == t.b) << 1) | (e.first == t.c) | ((e.first == t.c) << 1)) +
                    ((e.second == t.a) | ((e.second == t.b) << 1) | (e.second == t.c) | ((e.second == t.c) << 1)));
}

/****************************************************************************/

void DelaunayTriangulation::findCrossingEdges (Edge const &edge, CrossingEdgeList *crossingEdges, TrianglePtrVector *triangles) const
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

/**
 * Implementation based on BOOST.
 */
void DelaunayTriangulation::clipInfiniteEdge (const edge_type& edge, std::vector<point_type>* clipped_edge) const
{
        const cell_type& cell1 = *edge.cell ();
        const cell_type& cell2 = *edge.twin ()->cell ();
        point_type origin, direction;

        // Infinite edges could not be created by two segment sites.
        if (cell1.contains_point () && cell2.contains_point ()) {
                point_type const &p1 = input[cell1.source_index ()];
                point_type const &p2 = input[cell2.source_index ()];
                origin.x = (p1.x + p2.x) * 0.5;
                origin.y = (p1.y + p2.y) * 0.5;
                direction.x = p1.y - p2.y;
                direction.y = p2.x - p1.x;
        }

//        coordinate_type side = xh (brect_) - xl (brect_);
        coordinate_type side = 800;
        coordinate_type koef = side / (std::max) (fabs (direction.x), fabs (direction.y));

        if (edge.vertex0 () == NULL) {
                clipped_edge->push_back (Geometry::makePoint (origin.x - direction.x * koef, origin.y - direction.y * koef));
        }
        else {
                clipped_edge->push_back (Geometry::makePoint (edge.vertex0 ()->x (), edge.vertex0 ()->y ()));
        }
        if (edge.vertex1 () == NULL) {
                clipped_edge->push_back (Geometry::makePoint (origin.x + direction.x * koef, origin.y + direction.y * koef));
        }
        else {
                clipped_edge->push_back (Geometry::makePoint (edge.vertex1 ()->x (), edge.vertex1 ()->y ()));
        }
}

#endif /* DELAUNAYTRIANGULATION_H_ */
