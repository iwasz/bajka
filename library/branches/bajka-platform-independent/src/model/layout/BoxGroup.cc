/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BoxGroup.h"
#include "util/Exceptions.h"
#include "geometry/Ring.h"
#include "geometry/AffineMatrix.h"
#include "model/static/Box.h"
#include "model/static/Circle.h"
#include "BoxGroupProperties.h"

namespace Model {
using namespace boost::geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

void BoxGroup::update (Event::UpdateEvent *e)
{
        // TODO to nie powino się updejtować przy każdym odświerzeniu. Do wywalenia jest ta metoda.
        updateLayout ();
        Group::update (e);

}

void BoxGroup::updateLayout ()
{
        // W tym miejscu szerokość i wysokość samej grupy musi być już dobrze skorygowana na podstawie GroupProperies samej grupy.
        adjustMyDimensions (&w, &h);

        // Rozmieść i rozszerz dzieci.
        for (ModelVector::iterator i = children.begin (); i != children.end (); ++i) {
                IModel *child = *i;
                BoxGroupProperties *props = ((child->getGroupProps ()) ? (dynamic_cast <BoxGroupProperties *> (child->getGroupProps ())) : (NULL));

                if (!props) {
                        continue;
                }

                // Rozmiar dziecu AABB - tak zmienia rozmiar obiektu, żeby jego AABB stanowiło dany procent wysokości / szerokości tego BoxGroup:
                IBox *box = NULL;
                if ((props->getWidth () > 0 || props->getHeight () > 0) && (box = dynamic_cast <IBox *> (child))) {
                        if (child->getAngle () || child->getScale () != 1) {
                                throw Util::RuntimeException ("BoxGroup::updateLayout : width or height of an object was requested, but angle or scale is set. I don't know how to adjust AABB of objects with transformations applied.");
                        }

                        float w = 0, h = 0;
                        adjustChildrenDimensions (box, props, &w, &h);
                        box->setWidth (w);
                        box->setHeight (h);
                }

                // Pozycja dzieci :
                child->setTranslate (calculateTranslation (child, props));
        }
}

/****************************************************************************/

G::Point BoxGroup::calculateTranslation (IModel *child, BoxGroupProperties *props) const
{
        G::Box aabb = child->getBoundingBox ();
        float aabbW = aabb.getWidth ();
        float aabbH = aabb.getHeight ();

        G::Point tReq = props->getTranslate ();
        G::Point tAct = child->getTranslate ();
        G::Point ct;

        ct.x = ((tReq.x >= 0) ? (getWidth() * tReq.x / 100.0) : (tAct.x));
        ct.y = ((tReq.y >= 0) ? (getHeight () * tReq.y / 100.0) : (tAct.y));

        if (props->getAlign () == (BoxGroupProperties::TOP | BoxGroupProperties::RIGHT)) {
                return ct;
        }
        else {
                if (tReq.x >= 0) {
                        if (props->getAlign () & BoxGroupProperties::HCENTER) {
                                ct.x -= aabbW / 2.0;
                        }
                        else if (props->getAlign () & BoxGroupProperties::LEFT) {
                                ct.x -= aabbW;
                        }
                }

                if (tReq.y >= 0) {
                        if (props->getAlign () & BoxGroupProperties::VCENTER) {
                                ct.y -= aabbH / 2.0;
                        }
                        else if (props->getAlign () & BoxGroupProperties::BOTTOM) {
                                ct.y -= aabbH;
                        }
                }

                return ct;
        }
}

/****************************************************************************/

void BoxGroup::adjustMyDimensions (float *w, float *h)
{
        if (!getGroupProps () || )

        G::Box aabb;

        for (ModelVector::const_iterator i = children.begin (); i != children.end (); ++i) {
                if (i == children.begin ()) {
                        aabb = (*i)->getBoundingBox ();
                }
                else {
                        aabb.merge ((*i)->getBoundingBox ());
                }
        }

        G::Ring ring;
        G::Ring output;
        convert (aabb, ring);
        G::AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        envelope (output, aabb);
        *w = aabb.getWidth ();
        *h = aabb.getHeight ();
}

/****************************************************************************/

void BoxGroup::adjustChildrenDimensions (IBox *child, BoxGroupProperties *props, float *w, float *h)
{
        float reqW = props->getWidth ();
        float reqH = props->getHeight ();

        *w = ((reqW >= 0) ? (getWidth () * reqW / 100.0) : (child->getWidth ()));
        *h = ((reqH >= 0) ? (getHeight () * reqH / 100.0) : (child->getHeight ()));
}

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

G::Box BoxGroup::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
{
        G::Box aabb;
        G::Ring ring;
        G::Ring output;
        convert (getBox (), ring);
        G::AffineMatrixTransformer matrix (transformation);
        transform (ring, output, matrix);
        envelope (output, aabb);
        return aabb;
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

//void BoxGroup::setRelW (double w)
//{
//	BoxGroup *parGroup = getParGroup (this);
//
//	if (!parGroup) {
//		relW = w;
//		return;
//	}
//
//	setWidth (parGroup->getWidth () * w / 100.0);
//}
//
///****************************************************************************/
//
//void BoxGroup::setRelH (double h)
//{
//	BoxGroup *parGroup = getParGroup (this);
//
//	if (!parGroup) {
//		relH = h;
//		return;
//	}
//
//	setHeight (parGroup->getHeight () * h / 100.0);
//}

/****************************************************************************/

BoxGroup *BoxGroup::getParGroup (IModel *m)
{
        IModel *parent = m->getParent();

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

BoxGroup const *BoxGroup::getParGroup (IModel const *m)
{
        return getParGroup (const_cast <IModel *> (m));
}

} /* namespace Model */
