/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_BOX_H_
#define BAJKA_BOX_H_

#include "../geometry/AffineMatrix.h"
#include "../geometry/Point.h"
#include "Polygon.h"

namespace Model {

class Box : public Polygon {
public:

        Box (double x, double y, double w, double h) :  width (w), height (h) { setPosition (Geometry::Point (x, y)); }
        Box () : width (0), height (0) {}
        virtual ~Box () {}

        virtual Geometry::Point getPosition () const { return Geometry::Point (); }
        virtual void setPosition (Geometry::Point const &p) { }

        // TODO
        double getAngle () const { 0; }
        void setAngle (double a) { throw 1; }

        double getWidth () const { return width; }
        void setWidth (double w) { width = w; }

        double getHeight () const { return height; }
        void setHeight (double h) { height = h; }

        double calculateInertia (double mass) const;
        void parentCallback (IModel *m);

private:

        double width;
        double height;

};

} /* namespace Model1 */

#	endif /* BOX_H_ */
