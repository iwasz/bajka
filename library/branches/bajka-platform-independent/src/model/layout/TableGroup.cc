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
        // TODO to nie powino się updejtować przy każdym odświeżeniu.
        updateLayout ();
        Group::update (e);
}

/****************************************************************************/

void f (float a[]) {}

void TableGroup::updateLayout ()
{
        int remainder = children.size () % cols;
        int rows = children.size () / cols + bool (remainder);
        float colsW[cols];
        float rowsH[rows];
        float childW = 0, childH = 0;

        getChildrenDimensions (&childW, &childH, colsW, rowsH, cols, rows);
        adjustMyDimensions (childW, childH);

        float actualX = margin;
        float actualY = margin;

        for (int r = rows - 1; r >= 0; --r) {
                for (int c = 0; c < cols; ++c) {

                        unsigned int i = cols * r + c;
                        if (i >= children.size ()) {
                                continue;
                        }

                        Model::IModel *child = children[i];
                        G::Box aabb = child->getBoundingBox ();
                        G::Point t;
                        float aabbW = aabb.getWidth ();
                        float aabbH = aabb.getHeight ();

                        float cellW = colsW[c];
                        float cellH = rowsH[r];

                        // CENTER TODO inne opcje.
                        float cellX = (cellW - aabbW) / 2;
                        float cellY = (cellH - aabbH) / 2;

                        t.x = cellX + actualX;
                        actualX += cellW;

                        if (c < cols - 1) {
                                actualX += spacing;
                        }

                        t.y = cellY + actualY;

                        child->setTranslate (t);
                }

                actualX = margin;
                actualY += rowsH[r];

                if (r > 0) {
                        actualY += spacing;
                }
        }
}

/****************************************************************************/

void TableGroup::getChildrenDimensions (float *w,
                                        float *h,
                                        float colsW[],
                                        float rowsH[],
                                        int cols,
                                        int rows)
{
        if (heterogeneous) {
                float maxW = 0, maxH = 0;

                for (ModelVector::iterator i = children.begin (); i != children.end (); ++i) {
                        IModel *child = *i;
                        G::Box aabb = child->getBoundingBox ();
                        maxW = std::max (maxW, aabb.getWidth ());
                        maxH = std::max (maxH, aabb.getHeight ());
                }

                for (int r = 0; r < rows; ++r) {
                        rowsH[r] = maxH;
                }

                for (int c = 0; c < cols; ++c) {
                        colsW[c] = maxW;
                }

                *w = cols * maxW + (cols - 1) * spacing;
                *h = rows * maxH + (rows - 1) * spacing;

                return;
        }

        unsigned int i = 0;
        for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c, ++i) {

                        if (i >= children.size ()) {
                                goto breakAllLoops;
                        }

                        Model::IModel *child = children[i];
                        G::Box aabb = child->getBoundingBox ();
                        float aabbW = aabb.getWidth ();
                        float aabbH = aabb.getHeight ();

                        rowsH[r] = std::max (rowsH[r], aabbH);
                        colsW[c] = std::max (colsW[c], aabbW);
                }
        }

        breakAllLoops:

        for (int r = 0; r < rows; ++r) {
                *h += rowsH[r];
        }

        for (int c = 0; c < cols; ++c) {
                *w += colsW[c];
        }

        *w += (cols - 1) * spacing;
        *h += (rows - 1) * spacing;

        return;
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
