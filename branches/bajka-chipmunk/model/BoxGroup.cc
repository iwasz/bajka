/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BoxGroup.h"

namespace Model {
using namespace Geometry;

IModel *BoxGroup::findContains (Point const &p)
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

//        // --- Jeśli nie ma dzieci zwróć this.
        if (children.empty ()) {
                return this;
        }

        // --- Jeśli są dzieci, to przetransformuj p przez moją macierz i puść w pętli do dzieci.
        Point copy = p;
        transform (&copy);

        IModel *ret;

        for (ModelVector::iterator i = begin (); i != end (); ++i) {
                if ((ret = (*i)->findContains (p))) {
                        return ret;
                }
        }

        return this;
}


/****************************************************************************/

void BoxGroup::setChildren (ModelVector const &c)
{
        std::for_each (c.begin (), c.end (), boost::bind (&BoxGroup::addChild, this, _1));
}

/****************************************************************************/

void BoxGroup::addChild (IModel *m)
{
        children.push_back (m);
        m->setParent (this);
        m->parentCallback (this);
}

} /* namespace Model */
