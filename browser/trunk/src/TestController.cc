/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TestController.h"
#include <Platform.h>

#include <boost/polygon/voronoi.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/timer/timer.hpp>

#include <geometry/Ring.h>
#include <model/static/Ring.h>
#include "geometry/Point.h"
#include "TestView.h"
#include <stdint.h>

namespace boost {
namespace polygon {

template <>
struct geometry_concept<Geometry::Point> { typedef point_concept type; };

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

/*##########################################################################*/

/**
 *
 */
template<typename T>
struct my_voronoi_diagram_traits {
        typedef T coordinate_type;
        typedef boost::polygon::voronoi_cell<coordinate_type> cell_type;
        typedef boost::polygon::voronoi_vertex<coordinate_type> vertex_type;
        typedef boost::polygon::voronoi_edge<coordinate_type> edge_type;

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
        // Endpoints of a triangle.
        uint32_t a, b, c;

        // Adjacent triangles (opposite side of a, b, c).
        Triangle *A, *B, *C;
};

Triangle makeTriangle (uint32_t a, uint32_t b, uint32_t c)
{
        Triangle t;
        t.a = a;
        t.b = b;
        t.c = c;
        return t;
}

typedef std::vector <Triangle> TriangleVector;

std::ostream &operator<< (std::ostream &o, TriangleVector const &e)
{
        for (TriangleVector::const_iterator i = e.begin (); i != e.end (); ++i) {
                o << i->a << ", " << i->b << ", " << i->c << "\n";
        }

        return o;
}

// Data structure not optimized. Maybe some contiguous memory region can be used to eliminate memory partition and std::vector overhead.
typedef std::vector <Triangle *> TrianglePtrVector;

typedef std::vector <TrianglePtrVector> TriangleIndex;

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

/*##########################################################################*/

/**
 * Input must be in COUNTER CLOCKWISE order.
 */
// template
class DelaunayTriangulation {
public:

        DelaunayTriangulation (const Geometry::Ring& i, Geometry::LineString* v,
                        Geometry::LineString* d) :
                        input(i), voronoi(v), delaunay(d)
        {
                // -1 jest bo ostatni punkt nie moze być połączony sam ze sobą, a indeksem wiatraka jest mniejsza liczba z dwóch.
                // A kolejne -1 bo SVG ma ostatni punkt powtórzony.
                // TODO trzeba obsłużyć przypadek gdy ostatni powtórzony i gdy nie.
//                edgeFans.resize (input.size() - 2);
        }

        void constructDelaunay ();
        void constructDelaunay2 ();
        void constructDelaunay3 ();

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
                        const Geometry::Point& b);

        void addTriangle (uint32_t b, uint32_t c, size_t& a);


        // TODO do usunięcia lub przeniesienia.
        typedef double coordinate_type;
        typedef my_voronoi_diagram::vertex_type vertex_type;
        typedef my_voronoi_diagram::edge_type edge_type;
        typedef my_voronoi_diagram::cell_type cell_type;
        typedef Geometry::Point point_type;
        void clip_infinite_edge (const edge_type& edge, std::vector<point_type>* clipped_edge);

private:
        const Geometry::Ring&input;
        Geometry::LineString *voronoi;
        Geometry::LineString *delaunay;
        TriangleVector triangulation;
        TriangleIndex triangleIndex;
        EdgeFans edgeFans;
};

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
        size_t pointsSize = input.size ();

        int result = 0;
        for (my_voronoi_diagram::const_edge_iterator it = vd.edges ().begin (); it != vd.edges ().end (); ++it) {
                if (it->is_primary ()) {

                        ++result;

                        my_voronoi_diagram::vertex_type const *v0 = it->vertex0 ();
                        my_voronoi_diagram::vertex_type const *v1 = it->vertex1 ();

                        my_voronoi_diagram::edge_type const &edge = *it;
                        my_voronoi_diagram::edge_type const *twin = edge.twin ();

                        my_voronoi_diagram::cell_type const *cell = edge.cell ();
                        my_voronoi_diagram::cell_type const *nextCell = twin->cell ();

#if 0
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
                                clip_infinite_edge (*it, &samples);
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

        size_t cnt = 0;
        for (my_voronoi_diagram::const_vertex_iterator it = vd.vertices ().begin (); it != vd.vertices ().end (); ++it, ++cnt) {
                vertex_type const &vertex = *it;
                edge_type const *edge = vertex.incident_edge ();

                uint32_t triangleVertices[3];

                size_t edgeCnt = 0;
                do {
                        if (!edge->is_primary ()) {
                                continue;
                        }

                        cell_type const *cell = edge->cell ();
                        size_t index = cell->source_index ();
                        triangleVertices[edgeCnt++] = index;
                        edge = edge->rot_next ();

                        if (edgeCnt >= 3) {
                                break;
                        }
                } while (edge != vertex.incident_edge ());

                if (edgeCnt == 3) {
                        Triangle triangle;
                        triangle.a = triangleVertices[0];
                        triangle.b = triangleVertices[1];
                        triangle.c = triangleVertices[2];
                        triangulation.push_back (triangle);
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

/****************************************************************************/

bool DelaunayTriangulation::diagonalInside (Geometry::Point const &a, Geometry::Point const &ap, Geometry::Point const &an, Geometry::Point const &b)
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

void DelaunayTriangulation::clip_infinite_edge (const edge_type& edge, std::vector<point_type>* clipped_edge)
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

/*##########################################################################*/

void TestController::onPreUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v)
{
        if (firstTime) {
                firstTime = false;
        }
        else {
                return;
        }

        Model::Ring *ring = dynamic_cast<Model::Ring *> (m);
        Geometry::Ring *svg = ring->getData ();
        std::cerr << "SVG vertices : " << svg->size () << std::endl;

// Moja niedokończona implementacja
#if 1
        DelaunayTriangulation cdt (*svg, &voronoi, &delaunay);
        cdt.constructDelaunay ();
        cdt.constructDelaunay3 ();
#endif

        TestView *tv = dynamic_cast<TestView *> (v);
        tv->voronoi = &voronoi;
        tv->delaunay = &delaunay;
}
