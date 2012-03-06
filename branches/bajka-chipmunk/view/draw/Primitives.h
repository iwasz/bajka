/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_DRAWUTIL_H_
#define BAJKA_DRAWUTIL_H_

#include "Color.h"
#include "../../geometry/Point.h"
#include "../../geometry/Box.h"

namespace View {

struct DrawUtil {
public:

        static void drawCircle (Geometry::Point const &center, double angle, double radius, Color const &lineColor, Color const &fillColor);
        static void drawLine (Geometry::Point const &a, Geometry::Point const &b, Color const &color);
        static void drawRectangle (Geometry::Point const &a, Geometry::Point const &b, Color const &lineColor, Color const &fillColor);
        static void drawRectangle (Geometry::Box const &b, Color const &lineColor, Color const &fillColor);

        static void drawFatLine (Geometry::Point const &a, Geometry::Point const &b, double radius, Color const &lineColor, Color const &fillColor);
//        static void drawPolygon (int count, cpVect *verts, Color lineColor, Color fillColor);
//        static void drawPoints (cpFloat size, int count, cpVect *verts, Color color);
//        static void drawBox (Geometry::Box const &b, Color const &color);
};

}

#	endif /* DRAWUTIL_H_ */
