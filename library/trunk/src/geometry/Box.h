/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GEOMETRY_MODEL_BOX_H_
#define GEOMETRY_MODEL_BOX_H_

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/register/box.hpp>
#include <Object.h>
#include "Point.h"

namespace Geometry {

/**
 * Box Type.
 * <pre>
 *             +----+ ur (x2, y2)
 *             |    |
 * ll (x1, y1) +----+
 * </pre>
 * \ingroup Geometry
 */
class Box : public Core::IToStringEnabled {
public:
        C__ (void)
        Box () {}
        Box (const Point &ll, const Point &ur) : ll (ll), ur (ur) {}
        Box (double a, double b, double c, double d) { ll.x = a; ll.y = b; ur.x = c; ur.y = d; }
        C_ (std::string const &)
        Box (std::string const &s);
        virtual ~Box () {}

/*------access-methods------------------------------------------------------*/

        /// Zwraca różnicę miedzy ur a ll
        double getWidth () const { return ur.x - ll.x; }
        // Zmienia szerokość nie ruszając ll.
        void setWidth (double w) { ur.x = ll.x + w; }
        /// Zwraca różnicę miedzy ur a ll
        double getHeight () const { return ur.y - ll.y; }
        // Zmienia wysokość nie ruszając ll.
        void setHeight (double h) { ur.y = ll.y + h; }

/*--------------------------------------------------------------------------*/

        bool contains (Geometry::Point const &p) const { return p.x >= ll.x && p.x <= ur.x && p.y >= ll.y && p.y <= ur.y; }
        void merge (Box const &b);

/*--------------------------------------------------------------------------*/

        std::string toString () const;

/*--------------------------------------------------------------------------*/

        static const Box ZERO_BOX;

public:

        Point ll;
        Point ur;

        E_ (Geometry::Box)
};

}

BOOST_GEOMETRY_REGISTER_BOX (Geometry::Box, Geometry::Point, ll, ur)

#	endif /* BOX_H_ */
