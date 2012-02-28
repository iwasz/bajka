/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BoxGroup.h"
#include "../util/Exceptions.h"
#include "../geometry/Ring.h"
#include "../geometry/AffineMatrix.h"
#include "../model/static/Box.h"
#include "../model/static/Circle.h"

namespace Model {
using namespace boost::geometry;
//using namespace Geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

bool BoxGroup::contains (G::Point const &p) const
{
        G::Ring ring;
        G::Ring output;
        convert (getBox (), ring);
        G::AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

G::Box BoxGroup::getBoundingBox () const
{
        G::Box aabb;
        G::Ring ring;
        G::Ring output;

        if (!expand) {
                convert (getBox (), ring);
                G::AffineMatrixTransformer matrix (getMatrix ());
                transform (ring, output, matrix);
                envelope (output, aabb);
                return aabb;
        }
        else {
                G::Box envel;

                for (ModelVector::const_iterator i = children.begin (); i != children.end (); ++i) {
                        if (i == children.begin ()) {
                                envel = (*i)->getBoundingBox ();
                        }
                        else {
                                envel.merge ((*i)->getBoundingBox ());
                        }
                }

                return envel;
        }
}

/****************************************************************************/

double BoxGroup::getWidth () const
{
        if (!expand) {
                return w;
        }
        else {
                return getBoundingBox ().getWidth ();
        }
}

/****************************************************************************/

double BoxGroup::getHeight () const
{
        if (!expand) {
                return h;
        }
        else {
                return getBoundingBox ().getHeight ();
        }
}

/****************************************************************************/

Geometry::Box BoxGroup::getBox () const
{
        if (!expand) {
                return Geometry::Box (0, 0, w - 1, h - 1);
        }
        else {
                return getBoundingBox ();
        }
}

/****************************************************************************/

IModel *BoxGroup::findContains (G::Point const &p)
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
        G::Point copy = p;
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

void BoxGroup::setChildren (ModelVector const &c)
{
        std::for_each (c.begin (), c.end (), boost::bind (&BoxGroup::addChild, this, _1));
}

/****************************************************************************/

void BoxGroup::addChild (IModel *m)
{
        children.push_back (m);
        m->setParent (this);
        m->onParentSet (this);
}

/****************************************************************************/

void BoxGroup::setRelW (double w)
{
	BoxGroup *parGroup = getParGroup ();

	if (!parGroup) {
		relW = w;
		return;
	}

	setWidth (parGroup->getWidth () * w / 100.0);
}

/****************************************************************************/

void BoxGroup::setRelH (double h)
{
	BoxGroup *parGroup = getParGroup ();

	if (!parGroup) {
		relH = h;
		return;
	}

	setHeight (parGroup->getHeight () * h / 100.0);
}

/****************************************************************************/

//void BoxGroup::setRelX (double x)
//{
//	BoxGroup *parGroup = getParGroup ();
//
//	if (!parGroup) {
//		relX = x;
//		return;
//	}
//
//	G::Point oldT = getTranslate ();
//	setTranslate (G::Point (parGroup->getWidth () * x / 100.0, oldT.y));
//}
//
///****************************************************************************/
//
//void BoxGroup::setRelY (double y)
//{
//	BoxGroup *parGroup = getParGroup ();
//
//	if (!parGroup) {
//		relY = y;
//		return;
//	}
//
//	G::Point oldT = getTranslate ();
//	setTranslate (G::Point (oldT.x, parGroup->getHeight () * y / 100.0));
//}

/****************************************************************************/

//void BoxGroup::onParentSet (IModel *m)
//{
//	// Uruchamiamy jeszcze raz, bo teraz mamy parenta (ułatwoenie dla kontenera).
//	if (relW >= 0.0) {
//		setRelW (relW);
//	}
//
//	if (relH >= 0.0) {
//		setRelH (relH);
//
//	}
//	if (relX >= 0.0) {
//		setRelX (relX);
//	}
//
//	if (relY >= 0.0) {
//		setRelY (relY);
//	}
//}

/****************************************************************************/

void BoxGroup::screenToGroup (Geometry::Point *p) const
{
        if (parent && parent->isGroup ()) {
                dynamic_cast <IGroup *> (parent)->screenToGroup (p);
        }

        getMatrix ().transform (p);
}

/****************************************************************************/

void BoxGroup::groupToScreen (Geometry::Point *p) const
{
        getMatrix ().getInversed ().transform (p);

        if (parent && parent->isGroup ()) {
                dynamic_cast <IGroup *> (parent)->groupToScreen (p);
        }
}

} /* namespace Model */
