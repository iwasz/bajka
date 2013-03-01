/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TestController.h"
#include <Platform.h>

#include <geometry/Ring.h>
#include <model/static/Ring.h>
#include "geometry/Point.h"
#include "TestView.h"
#include <stdint.h>

#include "delaunay/DelaunayTriangulation.h"

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
//
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
//
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


/*##########################################################################*/

/**
 * Input must be in COUNTER CLOCKWISE order.
 */
class VoronoiRenderer {
public:

        VoronoiRenderer (const Geometry::Ring& i, Geometry::LineString* v) :
                        input(i), voronoi(v)
        {
        }

        void construct ();

        // TODO do usunięcia lub przeniesienia.
        typedef double coordinate_type;
        typedef my_voronoi_diagram::vertex_type vertex_type;
        typedef my_voronoi_diagram::edge_type edge_type;
        typedef my_voronoi_diagram::cell_type cell_type;
        typedef Geometry::Point point_type;

private:

        void clipInfiniteEdge (const edge_type& edge, std::vector<point_type>* clipped_edge) const;

private:

        const Geometry::Ring &input;
        Geometry::LineString *voronoi;
};

/****************************************************************************/

void VoronoiRenderer::construct ()
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

/**
 * Implementation based on BOOST.
 */
void VoronoiRenderer::clipInfiniteEdge (const edge_type& edge, std::vector<point_type>* clipped_edge) const
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
        coordinate_type side = 200;
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

/*-------------------------------------------------------------------------*/
#if 0
//        TODO unit tests!
        // Unit testy.
        Geometry::Edge a, b;
        a.a.x = -1;
        a.a.y = 0;
        a.b.x = 1;
        a.b.y = 0;
        b.a.x = 0;
        b.a.y = 1;
        b.b.x = 0;
        b.b.y = -1;

        assert (Geometry::intersects (a, b));

        // Stykają się, ale nie przecinają.
        a.a.x = -1;
        a.a.y = 1;
        a.b.x = 1;
        a.b.y = 1;
        b.a.x = 0;
        b.a.y = 1;
        b.b.x = 0;
        b.b.y = -1;

        assert (!Geometry::intersects (a, b));

        Triangle t;
        t.a = 3;
        t.b = 2;
        t.c = 1;
        DelaunayTriangulation::Edge ed;
        ed.first = 3;
        ed.second = 2;
        assert (getEdgeSide (t, ed) == 3);

        ed.first = 1;
        ed.second = 3;
        assert (getEdgeSide (t, ed) == 2);

        ed.first = 1;
        ed.second = 2;
        assert (getEdgeSide (t, ed) == 1);
#endif
/*--------------------------------------------------------------------------*/

        Model::Ring *ring = dynamic_cast<Model::Ring *> (m);
        Geometry::Ring *svg = ring->getData ();

//        boost::geometry::correct (*svg);
        // Bo z SVG jakoś tak załadował, że 2 ostatnie są jak pierwszy.
        svg->resize (svg->size () - 2);
        std::cerr << "SVG vertices : " << svg->size () << std::endl;
//        std::cerr << boost::geometry::dsv (*svg) << std::endl;


        typedef std::vector <Delaunay::Point> Input;
        Input input;

        for (Geometry::Ring::const_iterator i = svg->begin (); i != svg->end (); ++i) {
                input.push_back (Delaunay::Point (i->x, i->y));
        }

        typedef Delaunay::DelaunayTriangulation <Input> MyTriagulation;
        MyTriagulation cdt (input/*, &voronoi, &delaunay, &crossing*/);
        cdt.constructDelaunay (&crossing);

        MyTriagulation::TriangleVector const &triangulation = cdt.getTriangulation ();

        // 5. Create debug output
//        Trójkąty
//        for (TriangleVector::const_iterator i = triangulation.begin (); i != triangulation.end (); ++i) {
//                delaunay->push_back (input[i->a]);
//                delaunay->push_back (input[i->b]);
//                delaunay->push_back (input[i->c]);
//        }

//        Krawedzie trójkątów
        for (MyTriagulation::TriangleVector::const_iterator i = triangulation.begin (); i != triangulation.end (); ++i) {
                Delaunay::Point const &a = input[Delaunay::a (*i)];
                Delaunay::Point const &b = input[Delaunay::b (*i)];
                Delaunay::Point const &c = input[Delaunay::c (*i)];

                // Wireframe
                delaunay.push_back (Geometry::makePoint (a.x, a.y));
                delaunay.push_back (Geometry::makePoint (b.x, b.y));
                delaunay.push_back (Geometry::makePoint (b.x, b.y));
                delaunay.push_back (Geometry::makePoint (c.x, c.y));
                delaunay.push_back (Geometry::makePoint (c.x, c.y));
                delaunay.push_back (Geometry::makePoint (a.x, a.y));

                // Trójkąty pełne
                delaunay2.push_back (Geometry::makePoint (a.x, a.y));
                delaunay2.push_back (Geometry::makePoint (b.x, b.y));
                delaunay2.push_back (Geometry::makePoint (c.x, c.y));
//                delaunay2->push_back (input[i->a]);
//                delaunay2->push_back (input[i->b]);
//                delaunay2->push_back (input[i->c]);
        }

/*--------------------------------------------------------------------------*/

        VoronoiRenderer vr (*svg, &voronoi);
        vr.construct ();

/*--------------------------------------------------------------------------*/


        TestView *tv = dynamic_cast<TestView *> (v);
        tv->voronoi = &voronoi;
        tv->delaunay = &delaunay;
        tv->delaunay2 = &delaunay2;
        tv->crossing = &crossing;
}
