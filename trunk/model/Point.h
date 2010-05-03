/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 16, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <List.h>
#include <Reflection.h>

namespace Model {

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

        Core::String toString (unsigned int = 0) const { return Core::String ("Point(") + x + ", " + y + ")"; }

/*--------------------------------------------------------------------------*/

        // TODO Unit tests.
        Point &operator+= (const Point &p) { x += p.x; y += p.y; return *this; }
        Point operator+ (const Point &p) const { Point tmp = *this; tmp += p; return tmp; }

        Point &operator-= (const Point &p) { x -= p.x; y -= p.y; return *this; }
        Point operator- (const Point &p) const { Point tmp = *this; tmp -= p; return tmp; }

        bool operator== (const Model::Point &p) const { return x == p.x && y == p.y; }

//        bool operator<= (const Model::Point &p) const { return x <= p.x || y <= p.y; }
//        bool operator< (const Model::Point &p) const { return x < p.x || y < p.y; }
//
//        bool operator>= (const Model::Point &p) const { return x >= p.x || y >= p.y; }
//        bool operator> (const Model::Point &p) const { return x > p.x || y > p.y; }

private:

        double x;
        double y;

        _e (Point)
};

//typedef Core::List <Point> PointList;
typedef std::list <Point> PointList;


class LinePattern {
public:

        LinePattern () : pattern (0) {}

        int getPattern() const { return pattern; }
        void setPattern(int pattern) { this->pattern = pattern; }

private:

        int pattern;

};

} // nam

//std::ostream &operator<< (std::ostream &o, const Model::Point &p)
//{
//        o << ""
//}

#	endif /* POINT_H_ */
