/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BoxGroup.h"
#include "../util/Exceptions.h"

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

	double w = parGroup->getWidth () * x / 100.0;
	double bw = box.getWidth ();

	box.ll.x = w;
	box.ur.x = box.ll.x + bw;
}

/****************************************************************************/

void BoxGroup::setRelY (double y)
{

}

/****************************************************************************/

void BoxGroup::parentCallback (IModel *m)
{
	// Uruchamiamy jeszcze raz, bo teraz mamy parenta.
	if (relW >= 0.0) {
		setRelW (relW);
	}

	if (relH >= 0.0) {
		setRelH (relH);
	}
}

} /* namespace Model */
