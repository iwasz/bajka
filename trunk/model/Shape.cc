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

///****************************************************************************/
//
//bool Shape::enclose (const Geometry::Point &p) const
//{
//        for (AbstractModel::const_iterator i = begin (); i != end (); ++i) {
//                if ((*i)->enclose (p)) {
//                        return true;
//                }
//        }
//
//        Geometry::Box tmp = getBoundingBox ();
//        tmp.setUR (tmp.getUR () - tmp.getLL ());
//        tmp.setLL (Geometry::Point (0, 0));
//
//        return boost::geometry::within (p, tmp);
//}
//
///****************************************************************************/
//
//Geometry::Point Shape::screenToModel (Geometry::Point const &p) const
//{
//        /*
//         * TODO Czy to jest OK z tym static? Na pewno nie thread safe. Nie jest ok, bo jak
//         * user przypisze ta funkcję na referencję, a potem jeszcze raz, to mu się zmieni.
//         */
//        /*static*/Geometry::Point ret;
//        ret = AbstractModel::screenToModel (p);
//        ret -= getBoundingBox ().getLL ();
//        return ret;
//}
//
///****************************************************************************/
//
//Geometry::Point Shape::modelToScreen (Geometry::Point const &p) const
//{
//        Geometry::Point ret;
//        ret = AbstractModel::modelToScreen (p);
//        ret += getBoundingBox ().getLL ();
//        return ret;
//}

}//nam
