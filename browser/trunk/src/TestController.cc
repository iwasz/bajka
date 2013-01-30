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

void TestController::onPreUpdate (Event::UpdateEvent *e, Model::IModel *m, View::IView *v)
{
        if (firstTime) {
                firstTime = false;
        }
        else {
                return;
        }

        Model::Ring *ring = dynamic_cast <Model::Ring *> (m);
        Geometry::Ring *svg = ring->getData ();
        std::cerr << "SVG vertices : " << svg->size () << std::endl;

        typedef boost::polygon::point_data <int> PPoint;
        std::vector <PPoint> points;
        points.push_back(PPoint(0, 0));
        points.push_back(PPoint(1, 6));

        for (Geometry::Ring::const_iterator i = svg->begin (); i != svg->end (); ++i) {
                points.push_back (PPoint (boost::math::iround (i->x), boost::math::iround (i->y)));
        }

        // Robi diagram
        voronoi_diagram <double> vd;
        construct_voronoi (points.begin(), points.end(), &vd);

        int result = 0;
        for (voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin(); it != vd.edges().end(); ++it) {
                if (it->is_primary()) {
                        ++result;

                        if (it->is_infinite ()) {
                                continue;
                        }
                        voronoi_diagram <double>::vertex_type const *v0 = it->vertex0 ();
                        voronoi_diagram <double>::vertex_type const *v1 = it->vertex1 ();

                        voronoi.push_back (Geometry::makePoint (v0->x (), v0->y ()));
                        voronoi.push_back (Geometry::makePoint (v1->x (), v1->y ()));
                }
        }

        TestView *tv = dynamic_cast <TestView *> (v);
        tv->voronoi = &voronoi;
        tv->delaunay = &delaunay;
        std::cerr << "Voronoi prim. edges : " << result << std::endl;

        /// Triangulacja
        for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin(); it != vd.cells().end(); ++it) {

                voronoi_diagram<double>::cell_type const &cell = *it;

                if (!cell.contains_point()) {
                        continue;
                }

                std::size_t indexA = cell.source_index ();
                PPoint const &a = points[indexA];
                //printf ("Cell #%ud contains a point: (%d, %d).\n", cell_index, x(p), y(p));

                // This is convenient way to iterate edges around Voronoi cell.
                voronoi_diagram<double>::edge_type const *edge = cell.incident_edge();
                do {
                        if (!edge->is_primary()) {
                                continue;
                        }

                        voronoi_diagram<double>::edge_type const *twin = edge->twin ();

                        if (!twin) {
                                continue;
                        }

                        voronoi_diagram<double>::cell_type const *cellB = twin->cell ();

                        if (!cellB->contains_point ()) {
                                continue;
                        }

                        std::size_t indexB = cellB->source_index ();
                        PPoint const &b = points[indexB];

                        // TODO powtórzenia.
                        delaunay.push_back (Geometry::makePoint (a.x (), a.y ()));
                        delaunay.push_back (Geometry::makePoint (b.x (), b.y ()));

                        edge = edge->next();
                } while (edge != cell.incident_edge());
        }

}

