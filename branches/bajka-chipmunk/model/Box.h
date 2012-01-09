/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_BOX_H_
#define BAJKA_BOX_H_

#include "Polygon.h"
#include "../geometry/Point.h"
#include "../geometry/AffineMatrix.h"

namespace Model {

class Box : public Polygon {
public:

        Box (double x, double y, double w, double h) : position (x, y), width (w), height (h) {}
        Box () : width (0), height (0) {}
        virtual ~Box () {}

        Geometry::Point getPosition () const { return position; }
        void setPosition (Geometry::Point const &p) { position = p; }

        // TODO
        double getAngle () const { throw 1; }
        void setAngle (double a) { matrix.rotate (a); }

        double const *getMatrix () const { return matrix.data ().begin (); }

        double getWidth () const { return width; }
        void setWidth (double w) { width = w; }

        double getHeight () const { return height; }
        void setHeight (double h) { height = h; }

private:

        Geometry::Point position;
        double width;
        double height;
        Geometry::AffineMatrix matrix;

};

} /* namespace Model1 */

#	endif /* BOX_H_ */
