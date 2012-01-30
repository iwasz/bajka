/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include "Box.h"
#include "../../geometry/Ring.h"

namespace Model {
using namespace boost::geometry;
using namespace Geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

Geometry::Point Box::computeCenter () const
{
        return Point ((box.ll.x + box.ur.x) / 2.0, (box.ll.y + box.ur.y) / 2.0);
}

/****************************************************************************/

IModel *Box::findContains (Point const &p)
{
        // - Punkt p jest we współrzędnych rodzica.

        // A.
        // - Weź mój aabb we wsp. rodzica, czyli równoległy do osi układu rodzica.
        // -- Przetransformuj ll i ur
        // --- Stwórz macierz.
        // --- Przemnóż ll i ur przez tą macierz.
        // -- Znajdz aabb (max i min x + max i min.y).
        G::Box aabb = getBoundingBox ();

        // - Sprawdź, czy p jest w aabb
        // -- Jeśli nie, zwróć NULL.

        if (!aabb.contains (p)) {
                return NULL;
        }

        // -- Jeśli tak, to sprawdź dokładnie, za pomocą inside
        if (!this->contains (p)) {
                return NULL;
        }

        // --- Jeśli nie ma dzieci zwróć this.
        if (!isContainer ()) {
                return this;
        }

        // --- Jeśli są dzieci, to przetransformuj p przez moją macierz i puść w pętli do dzieci.
        Point copy = p;
        transform (&copy);

        // Kastuj na kontener?
        IModel *ret;

        for (ModelVector::iterator i = begin (); i != end (); ++i) {
                if (ret = (*i)->findContains (p)) {
                        return ret;
                }
        }

        return this;
}

/****************************************************************************/

bool Box::contains (Point const &p) const
{
        Ring ring;
        convert (box, ring);

        double aRad = angle * M_PI / 180.0;
        double s = scale * sin (aRad);
        double c = scale * cos (aRad);
        Point ct = getCenter ();

        trans::ublas_transformer <Point, Point, 2, 2> matrix (
                c, -s, -c * ct.x + s * ct.y + ct.x + position.x,
                s,  c, -s * ct.x - c * ct.y + ct.y + position.y,
                0,  0,  1
        );

        Ring output;
        boost::geometry::transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

//void Box::transform (Point *p) const
//{
//        double aRad = angle * M_PI / 180.0;
//        // Pomnożyć sin i cos razy scale i podstawić.
//        double s = sin (aRad);
//        double c = cos (aRad);
//        double x = p->x;
//        Point ct = getCenter ();
//
//        p->x = scale * c * (x - scale * ct.x) + scale * s * (scale * ct.y - p->y) + ct.x + position.x;
//        p->y = scale * c * (p->y - scale * ct.y) + scale * s * (x - scale * ct.x) + ct.y + position.y;
//}

/****************************************************************************/

G::Box Box::getBoundingBox () const
{
        G::Box aabb;
        Ring ring;
        convert (box, ring);

        double aRad = angle * M_PI / 180.0;
        double s = scale * sin (aRad);
        double c = scale * cos (aRad);
        Point ct = getCenter ();

        trans::ublas_transformer <Point, Point, 2, 2> matrix (
    		c, -s, -c * ct.x + s * ct.y + ct.x + position.x,
    		s,  c, -s * ct.x - c * ct.y + ct.y + position.y,
    		0,  0,  1
	);

        Ring output;
        boost::geometry::transform (ring, output, matrix);
        envelope (output, aabb);
        return aabb;
}


} /* namespace Model */
