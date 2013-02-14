/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DELAUNAYTRIANGULATION_H_
#define DELAUNAYTRIANGULATION_H_

#include "DelaunayIndex.h"

#include <boost/polygon/voronoi.hpp>
#include <boost/math/special_functions/round.hpp>
#ifndef NDEBUG
#include <boost/timer/timer.hpp>
// TODO REMOVE THIS!!
#include <geometry/LineString.h>
#endif

namespace boost {
namespace polygon {

// TODO te traitsy nie mogą tak być!
template <>
struct geometry_concept<Delaunay::Point> {
        typedef point_concept type;
};

template<>
struct point_traits<Delaunay::Point> {
        typedef Delaunay::PointTraits <Delaunay::Point> DelaunayPointTraitsType;
        typedef DelaunayPointTraitsType::IntCoordinateType coordinate_type;

        /*
         * TODO sprawdzić jak często to się wykonuje i skąd. Jak tylko w kroku inicjacji, to OK.
         * Dał bym tutaj też mnożnik, żeby uniknąć sytuacji, kiedy dwa zmiennoprzecinkowe punkty
         * wejściowe, które są bardzo blisko siebie zostaną przez poniższy get zwróceone jako
         * ten sam punkt. Można albo mnożyć przez stała (np 1000), albo znaleźć najmniejszą różnicę
         * mięczy dwoma współrzednymi w danych wejściowych i przeskalować je odpowiednio.
         */
        static inline coordinate_type get (const Delaunay::Point& point, orientation_2d orient)
        {
                return (orient == HORIZONTAL) ? boost::math::iround (Delaunay::H::x (point)) : boost::math::iround (Delaunay::H::y (point));
        }
};

}
}

/**
 *
 */
template<typename T>
struct triangulation_voronoi_diagram_traits {
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
typedef boost::polygon::voronoi_diagram<double, triangulation_voronoi_diagram_traits <double> > triangulation_voronoi_diagram;

/*##########################################################################*/

namespace Delaunay {

/**
 * Input must be in COUNTER CLOCKWISE order.
 * TODO unit testy różnych małych funkcyjek.
 */
template <typename Input, typename Traits = DelaunayTriangulationTraits<> >
class DelaunayTriangulation {
public:

        typedef DelaunayIndex <Input, Traits> DelaunayIndexType;
        typedef typename DelaunayIndexType::PointType PointType;
        typedef typename DelaunayIndexType::PointTraitsType PointTraitsType;
        typedef typename DelaunayIndexType::CoordinateType CoordinateType;
        typedef typename DelaunayIndexType::EdgeType EdgeType;
        typedef typename DelaunayIndexType::TriangleType TriangleType;
        typedef typename DelaunayIndexType::TriangleTraitsType TriangleTraitsType;
        typedef typename DelaunayIndexType::IndexType IndexType;
        typedef typename DelaunayIndexType::TriangleEdgeType TriangleEdgeType;
        typedef std::list <TriangleEdgeType> TriangleEdgeList;
        typedef typename DelaunayIndexType::TriangleVector TriangleVector;
        typedef typename DelaunayIndexType::TrianglePtrVector TrianglePtrVector;
        typedef typename DelaunayIndexType::TriangleIndex TriangleIndex;
        typedef typename DelaunayIndexType::CrossingEdge CrossingEdge;
        typedef typename DelaunayIndexType::CrossingEdgeList CrossingEdgeList;
        typedef typename DelaunayIndexType::IntersectionInfo IntersectionInfo;

        typedef triangulation_voronoi_diagram::vertex_type vertex_type;
        typedef triangulation_voronoi_diagram::edge_type edge_type;
        typedef triangulation_voronoi_diagram::cell_type cell_type;

        DelaunayTriangulation (Input const &i) : input (i), index (i)
        {
                // TODO ***KRYTYCZNE*** ustawić tu tyle ile ma być. Da się to wyliczyć na początku!?
                triangulation.reserve (input.size () * 10);
        }

        // TODO remove crossing
        void constructDelaunay (Geometry::LineString *crossing);

        TriangleVector const &getTriangulation () const { return triangulation; }

private:

        /**
         * Returns if diagonal (a, b) lays completely inside the polygon. It assumes two things:
         * - Points in polygon are stored in counter clockwise order.
         * - Checked diagonal do not intersects with boundary segments (defined by polygon itself)
         * in points other than a and b.
         * This second condition is easy to conform to, since we operate on diagonals generated
         * by triangulation algotihm.
         */
        bool diagonalInside (PointType const& a,
                             PointType const& ap,
                             PointType const& an,
                             PointType const& b) const;

private:

        Input const &input;
        DelaunayIndexType index;
        TriangleVector triangulation;

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
void DelaunayTriangulation<Input, Traits>::constructDelaunay (Geometry::LineString *crossing)
{
        triangulation_voronoi_diagram vd;

#ifndef NDEBUG
        boost::timer::cpu_timer t0;
#endif

        construct_voronoi (input.begin (), input.end (), &vd);

#ifndef NDEBUG
        printlog ("Voronoi diagram construction time : %f ms", t0.elapsed ().wall / 1000000.0);
#endif

        boost::timer::cpu_timer t1;

        // 1. Make triangles from voronoi.
        for (triangulation_voronoi_diagram::const_vertex_iterator it = vd.vertices ().begin (); it != vd.vertices ().end (); ++it) {
                vertex_type const &vertex = *it;
                edge_type const *edge = vertex.incident_edge ();

                IndexType triangleVertices[3];
                IndexType triangleCnt = triangulation.size ();
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
                        TriangleType triangle;
                        a (triangle, triangleVertices[0]);
                        b (triangle, triangleVertices[1]);
                        c (triangle, triangleVertices[2]);
                        triangulation.push_back (triangle);
//                        std::cerr << triangulation << std::endl;

                        // Update triangle index.
                        TriangleType const *t = &triangulation.back ();
                        index.addTriangle (t);

//                        std::cerr << "Point " << triangle.a << " has incident triangle : " << *t << std::endl;
//                        std::cerr << "Point " << triangle.b << " has incident triangle : " << *t << std::endl;
//                        std::cerr << "Point " << triangle.c << " has incident triangle : " << *t << std::endl;
                }
        }

#ifndef NDEBUG
//        std::cerr << "Delaunay triangulation produced : " << triangulation.size () << " triangles." << std::endl;
#endif

        // 2. Link triangles.
        for (triangulation_voronoi_diagram::const_vertex_iterator it = vd.vertices ().begin (); it != vd.vertices ().end (); ++it) {
                vertex_type const &vertex = *it;
                TriangleType &triangle = triangulation[vertex.color ()];
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

                        TriangleType &adjacentTriangle = triangulation[adjacentIndex - 1];

                        // Sprawdzić którym bokiem się stykają i ustawić.
                        if (!hasVertex (adjacentTriangle, triangle.a)) {
                                triangle.tA = &adjacentTriangle; // TODO external index
                        }
                        else if (!hasVertex (adjacentTriangle, triangle.b)) {
                                triangle.tB = &adjacentTriangle; // TODO external index
                        }
                        else if (!hasVertex (adjacentTriangle, triangle.c)) {
                                triangle.tC = &adjacentTriangle; // TODO external index
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
        TriangleEdgeList missingConstraints;
        size_t inputSize = input.size ();

        for (size_t i = 0; i < inputSize; ++i) {
                size_t j = (i + 1) % inputSize;

                assert (index.getTriangleIndexSize () > i);
                TrianglePtrVector const &trianglesForPoint = index.getTrianglesForIndex (i);

#if 0
                if (trianglesForPoint.empty ()) {
                        std::cerr << "UWAGA : trianglesForPoint.empty () : nie ma trójkątów stycznych do punktu o indeksie : " << i << ". TODO rozkminić czy to OK. i_max = " << inputSize -1  << std::endl;
                }
#endif

                assert (!trianglesForPoint.empty ());

                bool found = false;
                for (typename TrianglePtrVector::const_iterator k = trianglesForPoint.begin (); k != trianglesForPoint.end (); ++k) {
                        if (hasEdge (**k, TriangleEdgeType (i, j))) {
                                found = true;
                                break;
                        }
                }

                if (!found) {
#if 1
                        std::cerr << "Constraint (" << i << ", " << j << ") was **NOT** found in triangulation." << std::endl;
#endif
                        missingConstraints.push_back (TriangleEdgeType (i, j));
                }
        }

        // 4. Add missing segments.
        for (typename TriangleEdgeList::const_iterator i = missingConstraints.begin (); i != missingConstraints.end (); ++i) {
                TriangleEdgeType const &missingConstraint = *i;

                if (missingConstraint.a != 450) {
                        continue;
                }
                std::cerr << "Missing constraint : " << missingConstraint << std::endl;

                CrossingEdgeList crossingEdges;
                TrianglePtrVector crossingTriangles;

                index.findCrossingEdges (missingConstraint, &crossingEdges, &crossingTriangles);

//                std::cerr << "Constraint " << missingConstraint << " crosses : " << crossingTriangles << std::endl;

#if 1
                // TODO Debug output - to się może przydac.
                for (typename TrianglePtrVector::const_iterator i = crossingTriangles.begin (); i != crossingTriangles.end (); ++i) {
                        Delaunay::Point const &a = input[Delaunay::a (**i)];
                        Delaunay::Point const &b = input[Delaunay::b (**i)];
                        Delaunay::Point const &c = input[Delaunay::c (**i)];

                        crossing->push_back (Geometry::makePoint (a.x, a.y));
                        crossing->push_back (Geometry::makePoint (b.x, b.y));
                        crossing->push_back (Geometry::makePoint (c.x, c.y));
                }
#endif

                TriangleEdgeList newEdges;
                typename CrossingEdgeList::iterator j = crossingEdges.begin ();
                while (!crossingEdges.empty ()) {
                        typename CrossingEdgeList::iterator next = j;
                        ++next;

                        CrossingEdge e = *j;

                        if (!index.twoTrianglesConvex (e)) {

                                std::cerr << "####> !CONVEX" << std::endl;
                                if (crossingEdges.size () == 1) {
                                        /*
                                         * TODO Jeśli jest tylko jedna przecinająca dany constraint, to jeśli convex,
                                         * to flip, a jeśli nie, to nie wiem, ale coś trzeba tu zrobić.
                                         */
                                }

                                j = next;
                                continue;
                        }

                        std::cerr << "####> +++CONVEX" << std::endl;

                        // Dwa przyległę trójkąty zawierające e tworzą czworobok wypukły.
                        crossingEdges.erase (j);
                        TriangleEdgeType newDiagonal;

                        /*
                         * Tu trzeba
                         * - uaktualnić wierzchołki trójkątów.
                         * - uaktualnić ich zlinkowane trójkąty.
                         * - uaktualnic triangleIndex (potrzebny w findCrossing edges).
                         */
                        index.flip (e, &newDiagonal);
//                        break;

//                        if (Delaunay::intersects (e.template get<0> (), newDiagonal)) {
//                                missingConstraints.push_back (newDiagonal);
//                        }
//                        else {
//                                newEdges.push_back (newDiagonal);
//                        }

                        j = next;
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
//        for (TriangleVector::const_iterator i = triangulation.begin (); i != triangulation.end (); ++i) {
//                delaunay->push_back (input[i->a]);
//                delaunay->push_back (input[i->b]);
//                delaunay->push_back (input[i->b]);
//                delaunay->push_back (input[i->c]);
//                delaunay->push_back (input[i->c]);
//                delaunay->push_back (input[i->a]);
//        }

#ifndef NDEBUG
        printlog ("Triangulation time (derived from voronoi as its dual) : %f ms", t1.elapsed ().wall / 1000000.0);
        //        printlog ("Voronoi prim. edges : %d", result);
//        std::cout << triangulation << std::endl;
#endif
}

/****************************************************************************/

template <typename Input, typename Traits>
bool DelaunayTriangulation <Input, Traits>::diagonalInside (PointType const &a, PointType const &ap, PointType const &an, PointType const &b) const
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

} // namespace

#endif /* DELAUNAYTRIANGULATION_H_ */
