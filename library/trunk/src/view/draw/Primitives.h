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
#include "../../model/VertexBuffer.h"

using Model::VertexBuffer;

namespace View {

struct DrawUtil {
public:

        static void drawCircle (Geometry::Point const &center, double angle, double radius, Color const &lineColor, Color const &fillColor);
        static void drawLine (Geometry::Point const &a, Geometry::Point const &b, Color const &color);
        static void drawRectangle (Geometry::Point const &a, Geometry::Point const &b, Color const &lineColor, Color const &fillColor);
        static void drawRectangle (Geometry::Box const &b, Color const &lineColor, Color const &fillColor);

        static void drawSegments (VertexBuffer const &buffer, Color const &lineColor, Color const &fillColor, float thickness);
        static void drawSegmentsPrettyJoin (VertexBuffer const &buffer, Color const &lineColor, Color const &fillColor, float thickness);

        static void drawThinSegments (VertexBuffer const &buffer, Color const &lineColor, Color const &fillColor);
        static void drawThickSegments (VertexBuffer const &buffer, Color const &lineColor, Color const &fillColor, float thickness);
        static void drawThickSegment (Geometry::Point const &a, Geometry::Point const &b, Color const &line, Color const &fill, float thickness);

        static int convertType (VertexBuffer::PointType type);

};

}

#	endif /* DRAWUTIL_H_ */
