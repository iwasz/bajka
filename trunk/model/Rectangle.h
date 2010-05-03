/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 17, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <List.h>
#include "Point.h"

namespace Model {

/**
 * Rect
 */
class Rectangle {
public:

        Rectangle () {}
        Rectangle (const Point &a, const Point &b) : a (a), b (b) {}
        Rectangle (double x1, double y1, double x2, double y2) : a (x1, y1), b (x2, y2) {}

        Point getA () const { return a; }
        void setA (const Point &a) { this->a = a; }

        Point getB () const { return b; }
        void setB (const Point &b) { this->b = b; }

private:

        Point a, b;

};

typedef Core::List <Rectangle> RectangleList;

} // nam

#	endif /* RECTANGLE_H_ */
