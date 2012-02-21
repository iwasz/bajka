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

namespace Model {
using namespace boost::geometry;
using namespace Geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

bool BoxGroup::contains (Point const &p) const
{
        Ring ring;
        Ring output;
        convert (getBox (), ring);
        AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

G::Box BoxGroup::getBoundingBox () const
{
        G::Box aabb;
        Ring ring;
        Ring output;

        if (!expand) {
                convert (getBox (), ring);
        }
        else {
                Box envel;

                for (ModelVector::const_iterator i = children.begin (); i != children.end (); ++i) {
                        if (i == children.begin ()) {
                                envel = (*i)->getBoundingBox ();
                        }
                        else {
                                envel.merge ((*i)->getBoundingBox ());
                        }
                }

                convert (envel, ring);
        }

        AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        envelope (output, aabb);
        return aabb;
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
                return w;
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

/****************************************************************************/

BoxGroup *BoxGroup::getParGroup ()
{
	IModel *parent = getParent();

	if (!parent) {
		return NULL;
	}

	if (!parent->isBox()) {
		throw Util::RuntimeException("BoxGroup : !parent->isBox ()");
	}

	if (!parent->isGroup()) {
		throw Util::RuntimeException("BoxGroup : !parent->isGroup()");
	}

	return static_cast<BoxGroup *>(parent);
}

/****************************************************************************/

BoxGroup const *BoxGroup::getParGroup () const
{
	return const_cast <BoxGroup *> (this)->getParGroup ();
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

void BoxGroup::setRelX (double x)
{
	BoxGroup *parGroup = getParGroup ();

	if (!parGroup) {
		relX = x;
		return;
	}

	Point oldT = getTranslate ();
	setTranslate (Point (parGroup->getWidth () * x / 100.0, oldT.y));
}

/****************************************************************************/

void BoxGroup::setRelY (double y)
{
	BoxGroup *parGroup = getParGroup ();

	if (!parGroup) {
		relY = y;
		return;
	}

	Point oldT = getTranslate ();
	setTranslate (Point (oldT.x, parGroup->getHeight () * y / 100.0));
}

/****************************************************************************/

void BoxGroup::parentCallback (IModel *m)
{
	// Uruchamiamy jeszcze raz, bo teraz mamy parenta (ułatwoenie dla kontenera).
	if (relW >= 0.0) {
		setRelW (relW);
	}

	if (relH >= 0.0) {
		setRelH (relH);

	}
	if (relX >= 0.0) {
		setRelX (relX);
	}

	if (relY >= 0.0) {
		setRelY (relY);
	}
}

} /* namespace Model */
