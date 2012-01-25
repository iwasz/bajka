/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BoxB.h"

namespace Model {

//void BoxB::setPosition (Geometry::Point const &p)
//{
//        double w = box.getWidth ();
//        double h = box.getHeight ();
//        box.ll = p;
//        box.ur = Geometry::Point (p.x + w, p.y + h);
//}

/****************************************************************************/

IModel *BoxB::findChild (Geometry::Point const &p)
{
        // - Punkt p jest we współrzędnych rodzica.

        // A.
        // - Weź mój aabb we wsp. rodzica, czyli równoległy do osi układu rodzica.
        // -- Przetransformuj ll i ur
        // --- Stwórz macierz.
        // --- Przemnóż ll i ur przez tą macierz.
        // -- Znajdz aabb (max i min x + max i min.y).
        // - Sprawdź, czy p jest w aabb
        // -- Jeśli nie, zwróć NULL.
        // -- Jeśli tak, to sprawdź dokładnie, za pomocą inside
        // --- Jeśli nie ma dzieci zwróć this.
        // --- Jeśli są dzieci, to przetransformuj p przez moją macierz i puść w pętli do dzieci.


}

/****************************************************************************/

bool BoxB::inside (Geometry::Point const &p) const
{
        return p.x >= box.ll.x && p.x <= box.ur.x && p.y >= box.ll.y && p.y <= box.ur.y;
}

/****************************************************************************/

void BoxB::transform (Geometry::Point *p)
{
        double aRad = angle * 180.0 / M_PI;
        double sin_ = sin (aRad);
        double cos_ = cos (aRad);

//        Pierwsze podejście nieudane:
//        p->x = scale * cos_ * (p->x + center.x + position.x) - scale * sin_ * (p->y + center.y + position.y) - center.x;
//        p->y = scale * cos_ * (p->y + center.y + position.y) + scale * sin_ * (p->x + center.x + position.x) - center.y;

        p->x = scale * cos_ * (p->x - scale * center.x) + scale * sin_ * (scale * center.y - p->y) + center.x + position.x;
        p->y = scale * cos_ * (p->y - scale * center.y) + scale * sin_ * (p->x - scale * center.x) + center.y + position.y;
}


} /* namespace Model */
