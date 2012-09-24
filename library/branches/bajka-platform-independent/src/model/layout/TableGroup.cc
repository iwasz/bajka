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
        float widthFirstChildInLongestRow = 0;;
        float widthLastChildInLongestRow = 0;
        float heightTallestInFirstRow = 0;
        float heightTallestInLastRow = 0;

        getChildrenDimensions (&childW, &childH, &widthFirstChildInLongestRow, &widthLastChildInLongestRow, &heightTallestInFirstRow, &heightTallestInLastRow);
        adjustMyDimensions (childW, childH);

        float actualX = margin;
        float actualY = margin;

        float equalSpaceW = 0;
        float equalSpaceH = 0;


        if (children.size () > 1) {
                equalSpaceW = (w - 2 * margin - widthFirstChildInLongestRow / 2 - widthLastChildInLongestRow / 2) / (children.size () - 1);
                equalSpaceH = (h - 2 * margin - heightTallestInFirstRow / 2 - heightTallestInLastRow / 2) / (children.size () - 1);
        }

        int remainder = children.size () % cols;
        int rows = children.size () / cols + bool (remainder);

        unsigned int i = 0;
        for (int c = 0; c < cols; ++c) {
                float rowWidth = 0;
                float rowHeight = 0;

                actualX = margin;

                for (int r = 0; r < rows; ++r, ++i) {

                        if (i >= children.size ()) {
                                goto breakAllLoops;
                        }

                        Model::IModel *child = children[i];
                        G::Box aabb = child->getBoundingBox ();
                        float aabbW = aabb.getWidth ();
                        float aabbH = aabb.getHeight ();
                        G::Point t;

                        t.x = actualX;
                        t.y = (h - aabbH) / 2;

                        if (i < children.size ()) {
                                IModel *nextChild = children[i + 1];
                                actualX += equalSpaceW + (aabbW / 2) - (nextChild->getBoundingBox ().getWidth () / 2);
                        }

                        child->setTranslate (t);
                }
        }

        breakAllLoops:

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

void TableGroup::getChildrenDimensions (float *w,
                                        float *h,
                                        float *widthFirstChildInLongestRow,
                                        float *widthLastChildInLongestRow,
                                        float *heightTallestInFirstRow,
                                        float *heightTallestInLastRow)
{
        G::Box aabb;
        float width = 0;
        float height = 0;

        int remainder = children.size () % cols;
        int rows = children.size () / cols + bool (remainder);
        unsigned int i = 0;

        for (int r = 0; r < rows; ++r) {
                float rowWidth = 0;
                float rowHeight = 0;
                float widthFirstChild = 0;
                float widthLastChild = 0;

                for (int c = 0; c < cols; ++c, ++i) {

                        if (i >= children.size ()) {
                                goto breakAllLoops;
                        }

                        Model::IModel *model = children[i];
                        aabb = model->getBoundingBox ();

                        float aabbW = aabb.getWidth ();
                        rowWidth += aabbW;
                        rowHeight = std::max (height, aabb.getHeight ());

                        if (c == 0) {
                                widthFirstChild = aabbW;
                        }
                        else if (c == cols - 1) {
                                widthLastChild = aabbW;
                        }
                }

                if (rowWidth > width) {
                        width = rowWidth;
                        *widthFirstChildInLongestRow = widthFirstChild;
                        *widthLastChildInLongestRow = widthLastChild;
                }

                height += rowHeight;

                if (r == 0) {
                        *heightTallestInFirstRow = rowHeight;
                }
                else if (r == rows - 1) {
                        *heightTallestInLastRow = rowHeight;
                }
        }

        breakAllLoops:

        *w = width + spacing * (children.size () - 1);
        *h = height + spacing * (children.size () - 1);
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
