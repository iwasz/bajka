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
#include <List.h>
#include <Reflection.h>
#include <IToStringEnabled.h>

#include <boost/geometry/geometries/cartesian2d.hpp>
#include <boost/geometry/geometries/adapted/c_array_cartesian.hpp>
#include <boost/geometry/geometries/register/point.hpp>

namespace Model2 {

/**
 * Punkt.
 */
class Point : public Core::IToStringEnabled {
public:
        __c (void)

        Point () : x (0.0), y (0.0) {}
        explicit Point (double d) : x (d), y (d) {}
        Point (double x, double y) : x (x), y (y) {}

        double getX () const { return x; }
        _m (setX) void setX (double x) { this->x = x; }

        double getY () const { return y; }
        _m (setY) void setY (double y) { this->y = y; }

/*--------------------------------------------------------------------------*/

        Core::String toString (unsigned int = 0) const;

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

private:

        double x;
        double y;

        _e (Model2::Point)
};

} // namespace

/*
 * Can't pass 'Model2::Point' to BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET (:: chars confuse
 * those macros).
 */
typedef Model2::Point __BAJKA_POINT__;

/*
 * Register my custom point Type.
 */
BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET (__BAJKA_POINT__, double, cs::cartesian, getX, getY, setX, setY)

#	endif /* POINT_H_ */
