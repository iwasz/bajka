/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MODEL_BOX_H_
#define MODEL_BOX_H_

#include <boost/geometry/geometries/register/box.hpp>
#include <Object.h>

#include "Point.h"

namespace Geometry {

/**
 * Box Type.
 *
 *          +----+ (x2, y2)
 *          |    |
 * (x1, y1) +----+
 */
class Box : public Core::IToStringEnabled, virtual public Core::Object {
public:
        __c (void)

        Box () : x1 (0.0), y1 (0.0), x2 (0.0), y2 (0.0) {}
        Box (double a, double b, double c, double d) : x1 (a), y1 (b), x2 (c), y2 (d) {}
        virtual ~Box () {}

/*------access-methods------------------------------------------------------*/

        double getX1 () const { return x1; }
        _m (setX1) void setX1 (double x) { this->x1 = x; }

        double getY1 () const { return y1; }
        _m (setY1) void setY1 (double y) { this->y1 = y; }

        double getX2 () const { return x2; }
        _m (setX2) void setX2 (double x) { this->x2 = x; }

        double getY2 () const { return y2; }
        _m (setY2) void setY2 (double y) { this->y2 = y; }

/*--------------------------------------------------------------------------*/

        Core::String toString (unsigned int = 0) const;

/*--------------------------------------------------------------------------*/

private:

        double x1, y1; // Lower Left
        double x2, y2; // Upper right

        _e (Box)
};

}

typedef Geometry::Box __BAJKA_BOX__;

/*
 * BOOST definitions.
 */
namespace boost { namespace geometry { namespace traits {
        BOOST_GEOMETRY_DETAIL_SPECIALIZE_BOX_TRAITS(__BAJKA_BOX__, __BAJKA_POINT__)

        template <>
        struct indexed_access<__BAJKA_BOX__, min_corner, 0>
        {
            typedef coordinate_type<__BAJKA_POINT__>::type ct;
            static inline ct get(__BAJKA_BOX__ const& b) { return b.getX1 ();  }
            static inline void set(__BAJKA_BOX__& b, ct const& value) { b.setX1 (value); }
        };

        template <>
        struct indexed_access<__BAJKA_BOX__, min_corner, 1>
        {
            typedef coordinate_type<__BAJKA_POINT__>::type ct;
            static inline ct get(__BAJKA_BOX__ const& b) { return b.getY2 ();  }
            static inline void set(__BAJKA_BOX__& b, ct const& value) { b.setY2 (value); }
        };

        template <>
        struct indexed_access<__BAJKA_BOX__, max_corner, 0>
        {
            typedef coordinate_type<__BAJKA_POINT__>::type ct;
            static inline ct get(__BAJKA_BOX__ const& b) { return b.getX2 ();  }
            static inline void set(__BAJKA_BOX__& b, ct const& value) { b.setX2 (value); }
        };

        template <>
        struct indexed_access<__BAJKA_BOX__, max_corner, 1>
        {
            typedef coordinate_type<__BAJKA_POINT__>::type ct;
            static inline ct get(__BAJKA_BOX__ const& b) { return b.getY1 ();  }
            static inline void set(__BAJKA_BOX__& b, ct const& value) { b.setY1 (value); }
        };
}}}

#	endif /* BOX_H_ */
