/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GEOMETRY_MODEL_BOX_H_
#define GEOMETRY_MODEL_BOX_H_

//#include <boost/geometry/geometry.hpp>
//#include <boost/geometry/arithmetic/arithmetic.hpp>
//#include <boost/geometry/geometries/point_xy.hpp>
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
        Box (double a, double b, double c, double d) : ll (a, b), ur (c, d) {}
        C_ (std::string const &)
        Box (std::string const &s);
        virtual ~Box () {}

/*------access-methods------------------------------------------------------*/

        double getX1 () const { return ll.getX (); }
        m_ (setX1) void setX1 (double x) { ll.setX (x); }

        double getY1 () const { return ll.getY (); }
        m_ (setY1) void setY1 (double y) { ll.setY (y); }

        double getX2 () const { return ur.getX (); }
        m_ (setX2) void setX2 (double x) { ur.setX (x); }

        double getY2 () const { return ur.getY (); }
        m_ (setY2) void setY2 (double y) { ur.setY (y); }

        const Point &getLL () const { return ll; }
        const Point &getUR () const { return ur; }

        Point &getLL () { return ll; }
        Point &getUR () { return ur; }

        void setLL (const Point &p) { ll = p; }
        void setUR (const Point &p) { ur = p; }

        double getWidth () const { return getX2() - getX1 (); }
        double getHeight () const { return getY2 () - getY1 (); }

/*--------------------------------------------------------------------------*/

        std::string toString () const;

/*--------------------------------------------------------------------------*/

public:

        Point ll;
        Point ur;

        E_ (Box)
};

}

typedef Geometry::Box __BAJKA_BOX__;

///*
// * BOOST definitions.
// */
//namespace boost { namespace geometry { namespace traits {
//        BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_TRAITS(__BAJKA_BOX__, __BAJKA_POINT__)
//
//        template <>
//        struct indexed_access<__BAJKA_BOX__, min_corner, 0>
//        {
//            typedef coordinate_type<__BAJKA_POINT__>::type ct;
//            static inline ct get(__BAJKA_BOX__ const& b) { return b.getX1 ();  }
//            static inline void set(__BAJKA_BOX__& b, ct const& value) { b.setX1 (value); }
//        };
//
//        template <>
//        struct indexed_access<__BAJKA_BOX__, min_corner, 1>
//        {
//            typedef coordinate_type<__BAJKA_POINT__>::type ct;
//            static inline ct get(__BAJKA_BOX__ const& b) { return b.getY1 ();  }
//            static inline void set(__BAJKA_BOX__& b, ct const& value) { b.setY1 (value); }
//        };
//
//        template <>
//        struct indexed_access<__BAJKA_BOX__, max_corner, 0>
//        {
//            typedef coordinate_type<__BAJKA_POINT__>::type ct;
//            static inline ct get(__BAJKA_BOX__ const& b) { return b.getX2 ();  }
//            static inline void set(__BAJKA_BOX__& b, ct const& value) { b.setX2 (value); }
//        };
//
//        template <>
//        struct indexed_access<__BAJKA_BOX__, max_corner, 1>
//        {
//            typedef coordinate_type<__BAJKA_POINT__>::type ct;
//            static inline ct get(__BAJKA_BOX__ const& b) { return b.getY2 ();  }
//            static inline void set(__BAJKA_BOX__& b, ct const& value) { b.setY2 (value); }
//        };
//}}}

#	endif /* BOX_H_ */
