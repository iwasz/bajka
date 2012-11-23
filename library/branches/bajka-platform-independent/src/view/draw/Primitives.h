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
#include "geometry/Point.h"
#include "geometry/Box.h"

namespace Model {
class IModel;
class VertexBuffer;
}

namespace View {
class GLContext;

struct DrawUtil {
public:

//        static void drawCircle          (View::GLContext *ctx, Geometry::Point const &center, double angle, double radius, Color const &lineColor, Color const &fillColor, float thickness = 1);
//        static void drawLine            (View::GLContext *ctx, Geometry::Point const &a, Geometry::Point const &b, Color const &color, float thickness = 1);
        static void drawRectangle       (View::GLContext *ctx, Geometry::Point const &a, Geometry::Point const &b, Color const &lineColor, Color const &fillColor, float thickness = 1);
        static void drawRectangle       (View::GLContext *ctx, Geometry::Box const &b, Color const &lineColor, Color const &fillColor, float thickness = 1);

//        static void drawSegments        (View::GLContext *ctx, Model::VertexBuffer const &buffer, Color const &lineColor, Color const &fillColor, float thickness);
//        static void drawSegmentsPrettyJoin (View::GLContext *ctx, Model::VertexBuffer const &buffer, Color const &lineColor, Color const &fillColor, float thickness);

//        static int convertType          (Model::VertexBuffer::PointType type);
//        static void drawThinSegments    (View::GLContext *ctx, Model::VertexBuffer const &buffer, Color const &lineColor, Color const &fillColor);
//        static void drawThickSegments   (View::GLContext *ctx, Model::VertexBuffer const &buffer, Color const &lineColor, Color const &fillColor, float thickness);
//        static void drawThickSegment    (View::GLContext *ctx, Geometry::Point const &a, Geometry::Point const &b, Color const &line, Color const &fill, float thickness);
//        static void drawPoints          (View::GLContext *ctx, Model::VertexBuffer const &buffer, Color const &Color, float size);

        static void drawAABB            (View::GLContext *ctx, Model::IModel *model);

};

}

#	endif /* DRAWUTIL_H_ */
