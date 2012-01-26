/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include "BoxB.h"
#include "../../geometry/Ring.h"

namespace Model {
using namespace boost::geometry;
using namespace Geometry;
namespace trans = boost::geometry::strategy::transform;

//void BoxB::setPosition (Point const &p)
//{
//        double w = box.getWidth ();
//        double h = box.getHeight ();
//        box.ll = p;
//        box.ur = Point (p.x + w, p.y + h);
//}

/****************************************************************************/

IModel *BoxB::findContains (Point const &p)
{
        // - Punkt p jest we współrzędnych rodzica.

        // A.
        // - Weź mój aabb we wsp. rodzica, czyli równoległy do osi układu rodzica.
        // -- Przetransformuj ll i ur
        // --- Stwórz macierz.
        // --- Przemnóż ll i ur przez tą macierz.
        // -- Znajdz aabb (max i min x + max i min.y).
        Box aabb = getBoundingBox ();

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

bool BoxB::contains (Point const &p) const
{
    Ring ring;
    convert (box, ring);

    double aRad = angle * M_PI / 180.0;
    double s = scale * sin (aRad);
    double c = scale * cos (aRad);

    trans::ublas_transformer <Point, Point, 2, 2> matrix (
    		c, -s, -c * center.x + s * center.y + center.x + position.x,
    		s,  c, -s * center.x - c * center.y + center.y + position.y,
    		0,  0,  1
	);

    Ring output;
    boost::geometry::transform (ring, output, matrix);
    return within (p, output);
}

/****************************************************************************/

void BoxB::transform (Point *p) const
{
        double aRad = angle * M_PI / 180.0;
        // Pomnożyć sin i cos razy scale i podstawić.
        double s = sin (aRad);
        double c = cos (aRad);
        double x = p->x;

        p->x = scale * c * (x - scale * center.x) + scale * s * (scale * center.y - p->y) + center.x + position.x;
        p->y = scale * c * (p->y - scale * center.y) + scale * s * (x - scale * center.x) + center.y + position.y;
}

/****************************************************************************/

Box BoxB::getBoundingBox () const
{
//        double minX, minY, maxX, maxY;
//
//        G::Point p = box.ll;
//        transform (&p);
//
//        minX = maxX = p.x;
//        minY = maxY = p.y;
//
//        p = G::Point (box.ll.x, box.ur.y);
//        transform (&p);
//
//        if (p.x < minX) minX = p.x;
//        else if (p.x > maxX) maxX = p.x;
//        if (p.y < minY) minY = p.y;
//        else if (p.y > maxY) maxY = p.y;
//
//        p = box.ur;
//        transform (&p);
//
//        if (p.x < minX) minX = p.x;
//        else if (p.x > maxX) maxX = p.x;
//        if (p.y < minY) minY = p.y;
//        else if (p.y > maxY) maxY = p.y;
//
//        p = G::Point (box.ur.x, box.ll.y);
//        transform (&p);
//
//        if (p.x < minX) minX = p.x;
//        else if (p.x > maxX) maxX = p.x;
//        if (p.y < minY) minY = p.y;
//        else if (p.y > maxY) maxY = p.y;
//
//        return G::Box (minX, minY, maxX, maxY);

	Box aabb;
    Ring ring;
    convert (box, ring);

    double aRad = angle * M_PI / 180.0;
    double s = scale * sin (aRad);
    double c = scale * cos (aRad);

    trans::ublas_transformer <Point, Point, 2, 2> matrix (
    		c, -s, -c * center.x + s * center.y + center.x + position.x,
    		s,  c, -s * center.x - c * center.y + center.y + position.y,
    		0,  0,  1
	);

    Ring output;
    boost::geometry::transform (ring, output, matrix);
	envelope (output, aabb);
	return aabb;
}


} /* namespace Model */
