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
#include <geometry/Ring.h>
#include <model/static/Ring.h>
#include "geometry/Point.h"
#include "TestView.h"

using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;


//typedef boost::polygon::point_data<int> PPoint;


//struct Geometry::Point {
//  float x;
//  float y;
//};

namespace boost {
namespace polygon {

template <>
struct geometry_concept<Geometry::Point> { typedef point_concept type; };

template <>
struct point_traits<Geometry::Point> {
  typedef int coordinate_type;

  /*
   * TODO sprawdzić jak często to się wykonuje i skąd. Jak tylko w kroku inicjacji, to OK.
   * Dał bym tutaj też mnożnik, żeby uniknąć sytuacji, kiedy dwa zmiennoprzecinkowe punkty
   * wejściowe, które są bardzo blisko siebie zostaną przez poniższy get zwróceone jako
   * ten sam punkt. Można albo mnożyć przez stała (np 1000), albo znaleźć najmniejszą różnicę
   * mięczy dwoma współrzednymi w danych wejściowych i przeskalować je odpowiednio.
   */
  static inline coordinate_type get(const Geometry::Point& point, orientation_2d orient) {
    return (orient == HORIZONTAL) ? boost::math::iround (point.x) : boost::math::iround (point.y);
  }
};

}
}

/*
 * TODO odkładając punkty do kolekcji voronoi i do delaunay trzeba sprawdzać powtórzenia, tak, aby dany odcinek
 * odłożyć tylko raz. W przeciwnym wypadku będzie nieoszczędność pamięci.
 *
 * Upewniec się, ze input jest posortowany, że poligon jest CCW lub CW - zobaczyć jak.
 *
 * Dodać sprawdzanie czy punkt kŧóry łączymy jest wewnatrz także w kodzie triangulateDegenerated
 */

static void triangulateDegenerated (voronoi_diagram<double>::vertex_type const *v, std::vector<Geometry::Point> const &points, Geometry::LineString *delaunay)
{
        printlog ("###triangulate degenerated");
        std::vector<std::size_t> indices;

        voronoi_diagram<double>::edge_type const *edge = v->incident_edge ();
        do {
                voronoi_diagram<double>::cell_type const *cell = edge->cell ();

                if (cell->contains_point ()) {
                        std::size_t index = cell->source_index ();
                        indices.push_back (index);
                }

                edge = edge->rot_next ();
        } while (edge != v->incident_edge ());

        // Czworobok - wystarczy przeciąć go po przekątnej. TODO możnaby jakoś minimalizować ostre kąty.
        if (indices.size () == 4) {
                Geometry::Point const &a = points[indices[0]];
                Geometry::Point const &b = points[indices[2]];
                delaunay->push_back (Geometry::makePoint (a.x, a.y));
                delaunay->push_back (Geometry::makePoint (b.x, b.y));
        }
}

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




//        std::vector<Geometry::Point> points;
//
//        for (Geometry::Ring::const_iterator i = svg->begin (); i != svg->end (); ++i) {
//                Geometry::Point p;
//                p.x = boost::math::iround (i->x);
//                p.y = boost::math::iround (i->y);
//                points.push_back (p);
//        }

        // Zamiast kopiowania możemy podać nasze dane w niezmienionej postaci.
        Geometry::Ring const &points = *svg;

        // Robi diagram
        voronoi_diagram<double> vd;
        construct_voronoi (points.begin (), points.end (), &vd);
        size_t pointsSize = points.size ();

        int result = 0;
        for (voronoi_diagram<double>::const_edge_iterator it = vd.edges ().begin (); it != vd.edges ().end (); ++it) {
                if (it->is_primary ()) {

                        ++result;

                        voronoi_diagram<double>::vertex_type const *v0 = it->vertex0 ();
                        voronoi_diagram<double>::vertex_type const *v1 = it->vertex1 ();
#if 1
                        voronoi_diagram<double>::edge_type const &edge = *it;
                        voronoi_diagram<double>::edge_type const *twin = edge.twin ();

                        voronoi_diagram<double>::cell_type const *cell = edge.cell ();
                        voronoi_diagram<double>::cell_type const *nextCell = twin->cell ();

                        /*
                         * Konstruuj GRAF delaunay - w wyniku mogą pojawić wielokaty większe niż trójkąty jeżeli w poblizuu siebie
                         * znajdą się więcej niż 3 cocircullar sites.
                         */
                        if (cell->contains_point () && nextCell->contains_point ()) {
                                // Start point of delaunay edge to be drawn.
                                std::size_t indexA = cell->source_index ();
                                Geometry::Point const &a = points[indexA];
                                Geometry::Point const &ap = points[(indexA == 0) ? (pointsSize - 1) : (indexA - 1)];
                                Geometry::Point const &an = points[(indexA == pointsSize - 1) ? (0) : (indexA + 1)];

                                // End point of delaunay edge to be drawn.
                                std::size_t indexB = nextCell->source_index ();
                                Geometry::Point const &b = points[indexB];

                                // Przy założeniu, że counter-clockwise
                                int apx = ap.x - a.x;
                                int apy = ap.y - a.y;
                                int anx = an.x - a.x;
                                int any = an.y - a.y;
                                int bx = b.x - a.x;
                                int by = b.y - a.y;

                                int apXan = apx * any - apy * anx;
                                int apXb = apx * by - apy * bx;
                                int bXan = bx * any - by * anx;

                                if ((apXan >= 0 && apXb >= 0 && bXan >= 0) ||
                                    (apXan < 0 && !(apXb < 0 && bXan < 0))) {
                                        // TODO powtórzenia.
                                        delaunay.push_back (Geometry::makePoint (a.x, a.y));
                                        delaunay.push_back (Geometry::makePoint (b.x, b.y));
                                }
                        }

                        // Znajdż degeneracje i trianguluj je
                        if (v0) {
                                // Check if number of incident edges to this vertex was computed earlier (and stored in color).
//                                if (v0->color ()) {
//                                        // Triangulate degenerated sub-polygon
//                                        triangulateDegenerated (v0, points, &delaunay);
//                                }

                                /*
                                 * Compute the number of incident edges of a voronoi vertex. If its more than 3, we have a degenerate
                                 * situation, where more than 3 site points are cocircullar, and the dual of voronoi graph will construct
                                 * polygon instead of triangle.
                                 */
                                int edgeCnt = 0;
                                voronoi_diagram<double>::edge_type const *edge = v0->incident_edge ();
                                do {
                                        ++edgeCnt;
                                        edge = edge->rot_next ();
                                } while (edge != v0->incident_edge ());

                                if (edgeCnt > 3) {
//                                        printlog ("### v0 %d", edgeCnt);
                                        v0->color (edgeCnt);
                                        // Triangulate degenerated sub-polygon
                                        triangulateDegenerated (v0, points, &delaunay);
                                }
                        }

//                        if (v1) {
//                                // Check if number of incident edges to this vertex was computed earlier (and stored in color).
////                                if (v1->color ()) {
////                                        // Triangulate degenerated sub-polygon
////                                        triangulateDegenerated (v1, points, &delaunay);
////                                }
//
//                                /*
//                                 * Compute the number of incident edges of a voronoi vertex. If its more than 3, we have a degenerate
//                                 * situation, where more than 3 site points are cocircullar, and the dual of voronoi graph will construct
//                                 * polygon instead of triangle.
//                                 */
//                                int edgeCnt = 0;
//                                voronoi_diagram<double>::edge_type const *edge = v1->incident_edge ();
//                                do {
//                                        ++edgeCnt;
//                                        edge = edge->next ();
//                                } while (edge != v1->incident_edge ());
//
//                                if (edgeCnt > 3) {
//                                        printlog ("### v1 %d", edgeCnt);
//                                        v1->color (edgeCnt);
//                                        // Triangulate degenerated sub-polygon
//                                        triangulateDegenerated (v1, points, &delaunay);
//                                }
//                        }
#endif
                        if (it->is_infinite ()) {
                                continue;
                        }

                        voronoi.push_back (Geometry::makePoint (v0->x (), v0->y ()));
                        voronoi.push_back (Geometry::makePoint (v1->x (), v1->y ()));
                }
        }

        TestView *tv = dynamic_cast<TestView *> (v);
        tv->voronoi = &voronoi;
        tv->delaunay = &delaunay;
        std::cerr << "Voronoi prim. edges : " << result << std::endl;

#if 0
        /// Triangulacja
        for (voronoi_diagram<double>::const_cell_iterator it = vd.cells ().begin (); it != vd.cells ().end (); ++it) {

                voronoi_diagram<double>::cell_type const &cell = *it;

                if (cell.is_degenerate ()) {
                        printlog("---> !cell.is_degenerate!");
                }

                if (!cell.contains_point ()) {
                        printlog("---> !cell.contains_point()");
                        continue;
                }

                std::size_t indexA = cell.source_index ();
                PPoint const &a = points[indexA];
                //printf ("Cell #%ud contains a point: (%d, %d).\n", cell_index, x(p), y(p));

                // This is convenient way to iterate edges around Voronoi cell.
                voronoi_diagram<double>::edge_type const *edge = cell.incident_edge ();
                do {
                        if (!edge->is_primary ()) {
                                printlog("---> !edge->is_primary()");
                                continue;
                        }

                        voronoi_diagram<double>::edge_type const *twin = edge->twin ();

                        if (!twin) {
                                printlog("---> !twin");
                                continue;
                        }

                        voronoi_diagram<double>::cell_type const *cellB = twin->cell ();

                        if (!cellB->contains_point ()) {
                                printlog("---> !cellB->contains_point ()");
                                continue;
                        }

                        std::size_t indexB = cellB->source_index ();
                        PPoint const &b = points[indexB];

                        // TODO powtórzenia.
                        delaunay.push_back (Geometry::makePoint (a.x (), a.y ()));
                        delaunay.push_back (Geometry::makePoint (b.x (), b.y ()));

                        edge = edge->next ();
                } while (edge != cell.incident_edge ());
        }
#endif

        for (voronoi_diagram<double>::const_vertex_iterator it = vd.vertices ().begin (); it != vd.vertices ().end (); ++it) {
                const voronoi_diagram<double>::vertex_type &vertex = *it;
                const voronoi_diagram<double>::edge_type *edge = vertex.incident_edge ();

                if (vertex.is_degenerate ()) {
                        printlog ("--->> vertex is degenerate");
                }

                int edgeCnt = 0;
                // This is convenient way to iterate edges around Voronoi vertex.
                do {
                        ++edgeCnt;
                        edge = edge->rot_next ();
                } while (edge != vertex.incident_edge ());

                // Degeneracja
                if (edgeCnt > 3) {
                        printlog ("vertex has %d edges", edgeCnt);
                }
        }

}

