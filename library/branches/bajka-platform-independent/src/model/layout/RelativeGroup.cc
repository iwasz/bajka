/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "RelativeGroup.h"
#include "util/Exceptions.h"
#include "geometry/Ring.h"
#include "geometry/AffineMatrix.h"
#include "model/static/Box.h"
#include "model/static/Circle.h"
#include "RelativeGroupProperties.h"
#include "Align.h"

namespace Model {
using namespace boost::geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

void RelativeGroup::update (Event::UpdateEvent *e)
{
        // TODO to nie powino się updejtować przy każdym odświerzeniu. Do wywalenia jest ta metoda.
        // Może używac jakiegoś cache child-objectów i sprawdzać czy coś im się zmieniło (na przykład za pomocą jakiegoś HASHa wyliczanego na podstawie translate, angle i size).
        updateLayout ();
        Group::update (e);
}

/****************************************************************************/

void RelativeGroup::updateLayout ()
{
        // Rozmieść i rozszerz dzieci.
        for (ModelVector::iterator i = children.begin (); i != children.end (); ++i) {
                IModel *child = *i;
                RelativeGroupProperties const *props = ((child->getGroupProps ()) ? (dynamic_cast <RelativeGroupProperties const *> (child->getGroupProps ())) : (NULL));

                if (!props) {
                        continue;
                }

                // Rozmiar dziecu AABB - tak zmienia rozmiar obiektu, żeby jego AABB stanowiło dany procent wysokości / szerokości tego RelativeGroup:
                IBox *box = NULL;
                if ((props->width > 0 || props->height > 0) && (box = dynamic_cast <IBox *> (child))) {
                        if (child->getAngle () || child->getScale () != 1) {
                                throw Util::RuntimeException ("RelativeGroup::updateLayout : width or height of an object was requested, but angle or scale is set. I don't know how to adjust AABB of objects with transformations applied.");
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

G::Point RelativeGroup::calculateTranslation (IModel *child, RelativeGroupProperties const *props) const
{
        G::Box aabb = child->getBoundingBox ();
        float aabbW = aabb.getWidth ();
        float aabbH = aabb.getHeight ();

        G::Point tReq = props->translate;
//        G::Point tAct = child->getTranslate ();
        G::Point ct;

//        Narazie robię tak, że translate jest zawsze brane pod uwagę, nawet jak jest nieustawione.
//        ct.x = ((tReq.x >= 0) ? (getWidth() * tReq.x / 100.0) : (tAct.x));
//        ct.y = ((tReq.y >= 0) ? (getHeight () * tReq.y / 100.0) : (tAct.y));
        ct.x = getWidth() * tReq.x / 100.0;
        ct.y = getHeight () * tReq.y / 100.0;

        if (props->hAlign == HA_RIGHT && props->vAlign == VA_TOP) {
                // zwróć ct, ct jest gotowe.
        }
        else {
                if (tReq.x >= 0) {
                        if (props->hAlign == HA_CENTER) {
                                ct.x -= aabbW / 2.0;
                        }
                        else if (props->hAlign == HA_LEFT) {
                                ct.x -= aabbW;
                        }
                }

                if (tReq.y >= 0) {
                        if (props->vAlign == VA_CENTER) {
                                ct.y -= aabbH / 2.0;
                        }
                        else if (props->vAlign == VA_BOTTOM) {
                                ct.y -= aabbH;
                        }
                }

        }

        return ct;
}

/****************************************************************************/

void RelativeGroup::adjustChildrenDimensions (IBox *child, RelativeGroupProperties const *props, float *w, float *h)
{
        float reqW = props->width;
        float reqH = props->height;

        *w = ((reqW >= 0) ? (getWidth () * reqW / 100.0) : (child->getWidth ()));
        *h = ((reqH >= 0) ? (getHeight () * reqH / 100.0) : (child->getHeight ()));
}

/****************************************************************************/

bool RelativeGroup::contains (G::Point const &p) const
{
        G::Ring ring;
        G::Ring output;
        convert (getBox (), ring);
        G::AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

G::Box RelativeGroup::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
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

IModel *RelativeGroup::findContains (G::Point const &p)
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

//void RelativeGroup::addChild (IModel *m)
//{
//        Group::addChild (m);
//        ChildInfo c;
//        G::Point t = m->getTranslate ();
//        c.x = t.x;
//        c.y = t.y;
//        G::Box aabb = m->getBoundingBox ();
//        c.w = aabb.getWidth ();
//        c.h = aabb.getHeight ();
//        childInfo[m] = c;
//}

} /* namespace Model */
