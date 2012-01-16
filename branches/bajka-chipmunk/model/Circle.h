/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "../geometry/Point.h"
#include "Shape.h"

namespace Model {

class Circle : public Shape {
public:

        C__ (void)
        b_ ("Shape")

        virtual ~Circle () {}

        virtual void setPosition (Geometry::Point const &p);
        virtual Geometry::Point getPosition () const;

        double getRadius () const;
        m_ (setRadius) void setRadius (double r);

        double getAngle () const { return 0; }
        m_ (setAngle) void setAngle (double) {}

/*--------------------------------------------------------------------------*/

        double calculateInertia (double mass) const;
        virtual void parentCallback (IModel *m);

private:

        double radius;

        E_ (Model::Circle)

};

} /* namespace Model */

#	endif /* CIRCLE_H_ */
