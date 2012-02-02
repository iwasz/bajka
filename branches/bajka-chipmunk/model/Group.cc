/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include "Group.h"
#include "../geometry/Ring.h"

namespace Model {
using namespace Geometry;
using namespace boost::geometry;
namespace trans = boost::geometry::strategy::transform;

Box Group::getBoundingBox () const
{
	Box ret;

	for (ModelVector::const_iterator i = children.begin (); i != children.end (); ++i) {
		if (i == children.begin ()) {
			ret = (*i)->getBoundingBox ();
		}
		else {
			ret.merge ((*i)->getBoundingBox ());
		}
	}

//	// TODO Zdubloway kod Model::Box!
//    Ring ring;
//    convert (ret, ring);
//
//    double aRad = angle * M_PI / 180.0;
//    double s = scale * sin (aRad);
//    double c = scale * cos (aRad);
//    Point ct = getCenter ();
//
//    trans::ublas_transformer <Point, Point, 2, 2> matrix (
//		c, -s, -c * ct.x + s * ct.y + ct.x + translate.x,
//		s,  c, -s * ct.x - c * ct.y + ct.y + translate.y,
//		0,  0,  1
//    );
//
//    Ring output;
//    boost::geometry::transform (ring, output, matrix);
//    envelope (output, ret);

	return ret;
}

/****************************************************************************/

IModel *Group::findContains (Point const &p)
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

//        // --- Jeśli nie ma dzieci zwróć this.
        if (children.empty ()) {
                return this;
        }

        // --- Jeśli są dzieci, to przetransformuj p przez moją macierz i puść w pętli do dzieci.
        Point copy = p;
        getMatrix ().transform (&copy);

        IModel *ret;

        for (ModelVector::iterator i = begin (); i != end (); ++i) {
                if ((ret = (*i)->findContains (p))) {
                        return ret;
                }
        }

        return this;
}


/****************************************************************************/

void Group::setChildren (ModelVector const &c)
{
        std::for_each (c.begin (), c.end (), boost::bind (&Group::addChild, this, _1));
}

/****************************************************************************/

void Group::addChild (IModel *m)
{
        children.push_back (m);
        m->setParent (this);
        m->parentCallback (this);
}

} /* namespace Model */
