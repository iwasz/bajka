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

        static void drawThinSegments (void *buffer, size_t pointCnt, Color const &lineColor, Color const &fillColor);
        static void drawThickSegments (void *buffer, size_t pointCnt, Color const &lineColor, Color const &fillColor, float thickness);
        static void drawSegments (void *buffer, size_t pointCnt, Color const &lineColor, Color const &fillColor, float thickness);

        static void drawThickSegment (Geometry::Point const &a, Geometry::Point const &b, Color const &line, Color const &fill, float thickness);
};

}

#	endif /* DRAWUTIL_H_ */
