/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LinearGroup.h"
#include "util/Exceptions.h"
#include "geometry/Ring.h"
#include "geometry/AffineMatrix.h"
#include "model/static/Box.h"
#include "model/static/Circle.h"
#include "LinearGroupProperties.h"

namespace Model {
using namespace boost::geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

void LinearGroup::update (Event::UpdateEvent *e)
{
        // TODO to nie powino się updejtować przy każdym odświerzeniu. Do wywalenia jest ta metoda.
        updateLayout ();
        Group::update (e);

}

void LinearGroup::updateLayout ()
{
        // Szerokość i wysokość samej grupy jest tu korygowana na podstawie GroupProperies tej grupy.
        adjustMyDimensions ();

        float actualX = margin;
        float actualY = margin;

        // Rozmieść dzieci.
        for (ModelVector::iterator i = children.begin (); i != children.end (); ++i) {
                IModel *child = *i;
                LinearGroupProperties const *props = ((child->getGroupProps ()) ? (dynamic_cast <LinearGroupProperties const *> (child->getGroupProps ())) : (NULL));

                G::Box aabb = child->getBoundingBox ();
                float aabbW = aabb.getWidth ();
                float aabbH = aabb.getHeight ();
                G::Point t = child->getTranslate ();

                if (type == HORIZONTAL) {
                        t.x = actualX;
                        t.y = margin;
                        actualX += aabbW + spacing;
                }
                else {
                        t.x = margin;
                        t.y = actualY;
                        actualY += aabbH + spacing;
                }

                child->setTranslate (t);
        }
}

/****************************************************************************/

void LinearGroup::adjustMyDimensions ()
{
        if (!getWrapContentsW () && !getWrapContentsH ()) {
                return;
        }

        G::Box aabb;
        float width = 0;
        float height = 0;

        for (ModelVector::const_iterator i = children.begin (); i != children.end (); ++i) {
                aabb = (*i)->getBoundingBox ();

                if (type == HORIZONTAL) {
                        width += aabb.getWidth ();
                        height = std::max (height, aabb.getHeight ());
                }
                else {
                        width = std::max (height, aabb.getWidth ());
                        height += aabb.getHeight ();
                }
        }

        if (getWrapContentsW ()) {
                w = width + 2 * margin;

                if (type == HORIZONTAL) {
                        w += spacing * (children.size () - 1);
                }
        }

        if (getWrapContentsH ()) {
                h = height + 2 * margin;

                if (type == VERTICAL) {
                        h += spacing * (children.size () - 1);
                }
        }
}

/****************************************************************************/

bool LinearGroup::contains (G::Point const &p) const
{
        G::Ring ring;
        G::Ring output;
        convert (getBox (), ring);
        G::AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

G::Box LinearGroup::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
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

IModel *LinearGroup::findContains (G::Point const &p)
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
