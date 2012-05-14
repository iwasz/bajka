/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MODEL2_POINT_H_
#define MODEL2_POINT_H_

#include <iostream>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <IToStringEnabled.h>
#include "ReflectionMacros.h"

/**
 * Prymitywy geometryczne.
 */
namespace Geometry {

/**
 * Punkt.
 * \ingroup Geometry
 */
class Point : public Core::IToStringEnabled {
public:

        C__ (void)
        Point () : x (0.0), y (0.0) {}
        explicit Point (double d) : x (d), y (d) {}
        Point (double x, double y) : x (x), y (y) {}
        C_ (std::string const &)
        Point (std::string const &s);
        Point (const Point &p) : x (p.x), y (p.y) {}

/*--------------------------------------------------------------------------*/

        virtual std::string toString () const;

/*--------------------------------------------------------------------------*/

        Point &operator+= (const Point &p);
        Point operator+ (const Point &p) const { Point tmp = *this; tmp += p; return tmp; }

        Point &operator-= (const Point &p);
        Point operator- (const Point &p) const { Point tmp = *this; tmp -= p; return tmp; }

        Point &operator*= (const Point &p);
        Point operator* (const Point &p) const { Point tmp = *this; tmp *= p; return tmp; }

        Point &operator/= (const Point &p);
        Point operator/ (const Point &p) const { Point tmp = *this; tmp /= p; return tmp; }

        Point &operator+= (double d);
        Point operator+ (double d) const { Point tmp = *this; tmp += d; return tmp; }

        Point &operator-= (double d);
        Point operator- (double d) const { Point tmp = *this; tmp -= d; return tmp; }

        Point &operator*= (double d);
        Point operator* (double d) const { Point tmp = *this; tmp *= d; return tmp; }

        Point &operator/= (double d);
        Point operator/ (double d) const { Point tmp = *this; tmp /= d; return tmp; }

        bool operator== (const Point &p) const { return x == p.x && y == p.y; }
        bool operator== (double d) const { return x == d && y == d; }
        bool operator! () const { return x == 0.0 && y == 0.0; }

        double distance () const;
        double distance (Point const &p) const;

        static const Point ZERO_POINT;

public:

        double x;
        double y;

        E_ (Point)
};

/**
 * Wyrzucanie pinktu do strumienia.
 * \ingroup Geometry
 */
extern std::ostream &operator<< (std::ostream &o, Geometry::Point const &p);

} // namespace

/*
 * Register my custom point Type.
 */
BOOST_GEOMETRY_REGISTER_POINT_2D (Geometry::Point, double, cs::cartesian, x, y)

#	endif /* POINT_H_ */
