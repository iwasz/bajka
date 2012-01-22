/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BoxB.h"

namespace Model {

void BoxB::setPosition (Geometry::Point const &p)
{
        double w = box.getWidth ();
        double h = box.getHeight ();
        box.ll = p;
        box.ur = Geometry::Point (p.x + w, p.y + h);
}

/****************************************************************************/

IModel *BoxB::findChild (Geometry::Point const &p)
{

}

/****************************************************************************/

bool BoxB::inside (Geometry::Point const &p) const
{
        return p.x >= box.ll.x && p.x <= box.ur.x && p.y >= box.ll.y && p.y <= box.ur.y;
}


} /* namespace Model */
