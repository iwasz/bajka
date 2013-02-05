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

typedef std::vector <Triangle> TriangleVector;

// Data structure not optimized. Maybe some contiguous memory region can be used to eliminate memory partition and std::vector overhead.
typedef std::vector <Triangle *> TrianglePtrVector;

typedef std::vector <TrianglePtrVector> TriangleIndex;

/*##########################################################################*/

/**
 * Input must be in COUNTER CLOCKWISE order.
 */
// template
class DelaunayTriangulation {
public:

        DelaunayTriangulation (Geometry::Ring const &i, Geometry::LineString *v, Geometry::LineString *d) : input (i), voronoi (v), delaunay (d) {}

        void constructDelaunay ();

private:

        /**
         * Returns if diagonal (a, b) lays completely inside the polygon. It assumes two things:
         * - Points in polygon are stored in counter clockwise order.
         * - Checked diagonal do not intersects with boundary segments (defined by polygon itself)
         * in points other than a and b.
         * This second condition is easy to conform to, since we operate on diagonals generated
         * by triangulation algotihm.
         */
        bool diagonalInside (Geometry::Point const &a, Geometry::Point const &ap, Geometry::Point const &an, Geometry::Point const &b);

private:

        Geometry::Ring const &input;
        Geometry::LineString *voronoi;
        Geometry::LineString *delaunay;
        TriangleVector triangulation;
        TriangleIndex triangleIndex;

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
                                }
                        }

                        if (it->is_infinite ()) {
                                continue;
                        }

                        voronoi->push_back (Geometry::makePoint (v0->x (), v0->y ()));
                        voronoi->push_back (Geometry::makePoint (v1->x (), v1->y ()));
                }
        }

#ifndef NDEBUG
        printlog ("Triangulation time (derived from voronoi as its dual) : %f ms", t1.elapsed ().wall / 1000000.0);
        printlog ("Voronoi prim. edges : %d", result);
#endif
}

/****************************************************************************/

bool DelaunayTriangulation::diagonalInside (Geometry::Point const &a, Geometry::Point const &ap, Geometry::Point const &an, Geometry::Point const &b)
{
//        return true;
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
#endif

// Implemantacja z graphic gems - nie delaunay.
#if 0
        Geometry::Ring const &vertices = *svg;
        int n = vertices.size ();
        n = 5;

        // Computation
        int triangles[SEGSIZE][3];
        int nmonpoly;

        memset((void *)seg, 0, sizeof(seg));
        for (int i = 1; i <= n; i++)
          {
            seg[i].is_inserted = FALSE;

            seg[i].v0.x = vertices[i].x; /* x-cood */
            seg[i].v0.y = vertices[i].y; /* y-cood */
            if (i == 1)
              {
                seg[n].v1.x = seg[i].v0.x;
                seg[n].v1.y = seg[i].v0.y;
              }
            else
              {
                seg[i - 1].v1.x = seg[i].v0.x;
                seg[i - 1].v1.y = seg[i].v0.y;
              }
          }

        global.nseg = n;

        // initialization
        for (int i = 1; i <= n; i++) {
                seg[i].is_inserted = FALSE;
        }

        generate_random_ordering(n);

        construct_trapezoids(n, seg);
        nmonpoly = monotonate_trapezoids(n);
        triangulate_monotone_polygons(nmonpoly, triangles);
#endif

        TestView *tv = dynamic_cast<TestView *> (v);
        tv->voronoi = &voronoi;
        tv->delaunay = &delaunay;
}
