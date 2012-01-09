/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef VECTOR_GEOMETRY_H_
#define VECTOR_GEOMETRY_H_

#include <IToStringEnabled.h>

namespace Geometry {

class Vector : public Core::IToStringEnabled {
public:

        virtual ~Vector () {}

        Vector () : x (0.0), y (0.0) {}
        explicit Vector (double d) : x (d), y (d) {}
        Vector (double x, double y) : x (x), y (y) {}
        Vector (const Vector &p) : x (p.x), y (p.y) {}

/*--------------------------------------------------------------------------*/

        double getX () const { return x; }
        void setX (double x) { this->x = x; }

        double getY () const { return y; }
        void setY (double y) { this->y = y; }

/*--------------------------------------------------------------------------*/

        std::string toString () const;

/*--------------------------------------------------------------------------*/

//        Point &operator+= (const Point &p);
//        Point operator+ (const Point &p) const { Point tmp = *this; tmp += p; return tmp; }
//
//        Point &operator-= (const Point &p);
//        Point operator- (const Point &p) const { Point tmp = *this; tmp -= p; return tmp; }
//
//        Point &operator*= (const Point &p);
//        Point operator* (const Point &p) const { Point tmp = *this; tmp *= p; return tmp; }
//
//        Point &operator/= (const Point &p);
//        Point operator/ (const Point &p) const { Point tmp = *this; tmp /= p; return tmp; }
//
//        Point &operator+= (double d);
//        Point operator+ (double d) const { Point tmp = *this; tmp += d; return tmp; }
//
//        Point &operator-= (double d);
//        Point operator- (double d) const { Point tmp = *this; tmp -= d; return tmp; }
//
//        Point &operator*= (double d);
//        Point operator* (double d) const { Point tmp = *this; tmp *= d; return tmp; }
//
//        Point &operator/= (double d);
//        Point operator/ (double d) const { Point tmp = *this; tmp /= d; return tmp; }
//
//        bool operator== (const Point &p) const { return x == p.x && y == p.y; }
//        bool operator== (double d) const { return x == d && y == d; }
//        bool operator! () const { return x == 0.0 && y == 0.0; }

private:

        double x;
        double y;
};

} // namespace

extern std::ostream &operator<< (std::ostream &o, Geometry::Vector const &p);

#	endif /* VECTOR_H_ */
