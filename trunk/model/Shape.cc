/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/algorithms/within.hpp>
#include "Shape.h"

namespace Model {

bool Shape::enclose (const Geometry::Point &p) const
{
        Geometry::Box tmp = getBoundingBox ();
        tmp.setUR (tmp.getUR () - tmp.getLL ());
        tmp.setLL (Geometry::Point (0, 0));

        //std::cerr << "Shape::enclose p=(" << p << "), boundingBox=(" << getBoundingBox() << "), [" << boost::geometry::within (p, tmp) << "][" << AbstractModel::enclose (p) << "]" << std::endl;
        return boost::geometry::within (p, tmp) || AbstractModel::enclose (p);
}

/****************************************************************************/

Geometry::Point const &Shape::screenToModel (Geometry::Point const &p) const
{
        // TODO Czy to jest OK z tym static? Na pewno nie thread safe.
        static Geometry::Point ret;
        ret = AbstractModel::screenToModel (p);
        ret -= getBoundingBox ().getLL ();
        return ret;
}

/****************************************************************************/

Geometry::Point const &Shape::modelToScreen (Geometry::Point const &p) const
{
        // TODO Czy to jest OK z tym static? Na pewno nie thread safe.
        static Geometry::Point ret;
        ret = AbstractModel::modelToScreen (p);
        ret += getBoundingBox ().getLL ();
        return ret;
}

}//nam
