/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Layer.h"
#include "util/Exceptions.h"
#include "geometry/Ring.h"
#include "geometry/AffineMatrix.h"
#include "model/static/Box.h"
#include "model/static/Circle.h"
#include "LayerProperties.h"

namespace Model {
using namespace boost::geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

void Layer::update (Event::UpdateEvent *e)
{
        // TODO to nie powino się updejtować przy każdym odświerzeniu. Do wywalenia jest ta metoda.
        // Może używac jakiegoś cache child-objectów i sprawdzać czy coś im się zmieniło (na przykład za pomocą jakiegoś HASHa wyliczanego na podstawie translate, angle i size).
        updateLayout ();
        Group::update (e);
}

/****************************************************************************/

void Layer::updateLayout ()
{
        // Rozmieść i rozszerz dzieci.
        for (ModelVector::iterator i = children.begin (); i != children.end (); ++i) {
                IModel *child = *i;
                LayerProperties const *props = ((child->getGroupProps ()) ? (dynamic_cast <LayerProperties const *> (child->getGroupProps ())) : (NULL));

                if (!props || !child->isBox ()) {
                        continue;
                }

                IBox *box = dynamic_cast <IBox *> (child);

                adjustChildrenDimensions (child, box, props);

                if (!props->centerGroup || !child->isGroup ()) {
                        continue;
                }

                IGroup *group = dynamic_cast <IGroup *> (child);

                if (group->getCoordinateSystemOrigin () == IGroup::BOTTOM_LEFT) {
                        Geometry::Point t;
                        t.x = -box->getWidth () / 2.0;
                        t.y = -box->getHeight () / 2.0;
                        child->setTranslate (t);
                }
                else {
                        child->setTranslate (Geometry::ZERO_POINT);
                }
        }
}

/****************************************************************************/

void Layer::adjustChildrenDimensions (IModel *child, IBox *box, LayerProperties const *props)
{
        // Rozmiar dziecu AABB - tak zmienia rozmiar obiektu, żeby jego AABB stanowiło dany procent wysokości / szerokości tego Layer:
        if (props->fillW || props->fillW) {

                if (child->getAngle () || child->getScale () != 1) {
                        throw Util::RuntimeException ("Layer::updateLayout : width or height of an object was requested, but angle or scale is set. I don't know how to adjust AABB of objects with transformations applied.");
                }

                if (props->fillW) {
                        box->setWidth (getWidth ());
                }

                if (props->fillH) {
                        box->setHeight (getHeight ());
                }
        }
}

/****************************************************************************/

bool Layer::contains (G::Point const &p) const
{
        G::Ring ring;
        G::Ring output;
        convert (getBox (), ring);
        G::AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

G::Box Layer::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
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

IModel *Layer::findContains (G::Point const &p)
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

} /* namespace Model */
