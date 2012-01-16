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
#include "Shape.h"

namespace Model {

class Box : public Shape {
public:

        C__ (void)
        b_ ("Shape")

        Box (double x, double y, double w, double h) :  width (w), height (h) { setPosition (Geometry::Point (x, y)); }
        Box () : width (0), height (0) {}
        virtual ~Box () {}

        // Zawsze jest wypośrodkowane względem środka masy swojego body.
        virtual Geometry::Point getPosition () const { return Geometry::Point (); }
        virtual void setPosition (Geometry::Point const &p) { }

        // TODO
        double getAngle () const { 0; }
        void setAngle (double a) { throw 1; }

        double getWidth () const { return width; }
        m_ (setWidth) void setWidth (double w) { width = w; }

        double getHeight () const { return height; }
        m_ (setHeight) void setHeight (double h) { height = h; }

        double calculateInertia (double mass) const;
        void parentCallback (IModel *m);

private:

        double width;
        double height;

        E_ (Model::Box)
};

} /* namespace Model1 */

#	endif /* BOX_H_ */
