/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include "Circle.h"
#include "../../geometry/Ring.h"

namespace Model {
using namespace boost::geometry;
using namespace Geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

Geometry::Point Circle::computeCenter () const
{
        return origin;
}

/****************************************************************************/

IModel *Circle::findContains (Point const &p)
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
                if ((ret = (*i)->findContains (p))) {
                        return ret;
                }
        }

        return this;
}

/****************************************************************************/

bool Circle::contains (Point const &p) const
{
        // TODO!
        return true;
}

/****************************************************************************/

G::Box Circle::getBoundingBox () const
{
        double r = radius * scale;
        double x = translate.x + origin.x * scale;
        double y = translate.y + origin.y * scale;
        return G::Box (x - r, y - r, x + r, y + r);
}


} /* namespace Model */
