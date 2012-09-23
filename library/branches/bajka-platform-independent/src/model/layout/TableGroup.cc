/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TableGroup.h"
#include "util/Exceptions.h"
#include "geometry/Ring.h"
#include "geometry/AffineMatrix.h"
#include "model/static/Box.h"
#include "model/static/Circle.h"

namespace Model {
using namespace boost::geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

void TableGroup::update (Event::UpdateEvent *e)
{
        // TODO to nie powino się updejtować przy każdym odświerzeniu.
        updateLayout ();
        Group::update (e);
}

/****************************************************************************/

void TableGroup::updateLayout ()
{
        float childW = 0, childH = 0;
        getChildrenDimensions (&childW, &childH);

        // Szerokość i wysokość samej grupy jest tu korygowana na podstawie GroupProperies tej grupy.
        adjustMyDimensions (childW, childH);

        float actualX = 0;
        float actualY = 0;
        // Odległość między środkami obiektów jesli mamy gravity na CENTER.
        float equalSpace = 0;

        actualX = margin;

        if (children.size () > 1) {
                IModel *first = children.front ();
                IModel *last = children.back ();
                float firstW = first->getBoundingBox ().getWidth ();
                float lastW = last->getBoundingBox ().getWidth ();
                equalSpace = (w - 2 * margin - firstW / 2 - lastW / 2) / (children.size () - 1);
        }

        actualY = margin;

        if (children.size () > 1) {
                IModel *first = children.front ();
                IModel *last = children.back ();
                float firstH = first->getBoundingBox ().getHeight ();
                float lastH = last->getBoundingBox ().getHeight ();
                equalSpace = (h - 2 * margin - firstH / 2 - lastH / 2) / (children.size () - 1);
        }

        // Rozmieść dzieci.
        for (ModelVector::iterator i = children.begin (); i != children.end (); ++i) {
                IModel *child = *i;

                G::Box aabb = child->getBoundingBox ();
                float aabbW = aabb.getWidth ();
                float aabbH = aabb.getHeight ();
                G::Point t = child->getTranslate ();

//                if (type == HORIZONTAL) {
                        t.x = actualX;
                        t.y = (h - aabbH) / 2;

                        if (i + 1 != children.end ()) {
                                IModel *nextChild = *(i + 1);
                                actualX += equalSpace + (aabbW / 2) - (nextChild->getBoundingBox ().getWidth () / 2);
                        }
//                }
//                else {
                        t.y = actualY;
                        t.x = (w - aabbW) / 2;

                        if (i + 1 != children.end ()) {
                                IModel *nextChild = *(i + 1);
                                actualY += equalSpace + (aabbH / 2) - (nextChild->getBoundingBox ().getHeight () / 2);
                        }
//                }

                child->setTranslate (t);
        }
}

/****************************************************************************/

void TableGroup::getChildrenDimensions (float *w, float *h)
{
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
                        width = std::max (width, aabb.getWidth ());
                        height += aabb.getHeight ();
                }
        }

        *w = width;

        if (type == HORIZONTAL) {
                *w += spacing * (children.size () - 1);
        }

        *h = height;

        if (type == VERTICAL) {
                *h += spacing * (children.size () - 1);
        }
}

/****************************************************************************/

void TableGroup::adjustMyDimensions (float w, float h)
{
        if (getWrapContentsW ()) {
                this->w = w + 2 * margin;
        }

        if (getWrapContentsH ()) {
                this->h = h + 2 * margin;
        }
}

/****************************************************************************/

bool TableGroup::contains (G::Point const &p) const
{
        G::Ring ring;
        G::Ring output;
        convert (getBox (), ring);
        G::AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

G::Box TableGroup::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
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

IModel *TableGroup::findContains (G::Point const &p)
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
