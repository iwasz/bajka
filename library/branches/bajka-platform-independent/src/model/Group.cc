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
#include "../events/EventIdex.h"
#include "../events/PointerInsideIndex.h"

namespace Model {
using namespace Geometry;
using namespace boost::geometry;
namespace trans = boost::geometry::strategy::transform;

Box Group::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
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

//TODO to jest kopia z BoxGroup - wydzielić ten wspólny kod gdzieś.
IModel *Group::findContains (Point const &p)
{
        // - Punkt p jest we współrzędnych rodzica.

        // A.
        // - Weź mój aabb we wsp. rodzica, czyli równoległy do osi układu rodzica.
        // -- Przetransformuj ll i ur
        // --- Stwórz macierz.
        // --- Przemnóż ll i ur przez tą macierz.
        // -- Znajdz aabb (max i min x + max i min.y).
        Geometry::Box aabb = getBoundingBox ();

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
        if (children.empty ()) {
                return this;
        }

        // --- Jeśli są dzieci, to przetransformuj p przez moją macierz i puść w pętli do dzieci.
        Point copy = p;
        // TODO od razu można zwracać odwróconą.
        getMatrix ().getInversed ().transform (&copy);

        IModel *ret;

        for (ModelVector::reverse_iterator i = children.rbegin (); i != children.rend (); ++i) {
                if ((ret = (*i)->findContains (copy))) {
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
        m->onParentSet (this);

        if (eventIndex) {
                eventIndex->add (0xFFFFu & ~Event::MOUSE_EVENTS, m);

                if (m->isGroup ()) {
                        Model::IGroup *g = dynamic_cast <Model::IGroup *> (m);
                        g->setIndices (eventIndex, pointerInsideIndex);
                }
        }
}

/****************************************************************************/

void Group::popChild ()
{
        if (children.empty ()) {
                return;
        }

        IModel *back = children.back ();
        eventIndex->remove (back);
        pointerInsideIndex->remove (back);
        children.pop_back ();
}

/****************************************************************************/

void Group::screenToGroup (Geometry::Point *p) const
{
        if (parent && parent->isGroup ()) {
                dynamic_cast <IGroup *> (parent)->screenToGroup (p);
        }

        getMatrix ().transform (p);
}

/****************************************************************************/

void Group::groupToScreen (Geometry::Point *p) const
{
        getMatrix ().getInversed ().transform (p);

        if (parent && parent->isGroup ()) {
                dynamic_cast <IGroup *> (parent)->groupToScreen (p);
        }
}

/****************************************************************************/

IModel *Group::getTop ()
{
        return (children.empty ()) ? (NULL) : (children.back ());
}

/****************************************************************************/

void Group::setIndices (Event::EventIndex *e1, Event::PointerInsideIndex *e2)
{
        eventIndex = e1;
        pointerInsideIndex = e2;

        for (ModelVector::const_iterator i = children.begin (); i != children.end (); ++i) {
                if ((*i)->isGroup ()) {
                        Model::IGroup *g = dynamic_cast <Model::IGroup *> (*i);
                        g->setIndices (e1, e2);
                }
        }
}

} /* namespace Model */
