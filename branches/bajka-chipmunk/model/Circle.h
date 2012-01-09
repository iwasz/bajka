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

        virtual ~Circle () {}

        double getRadius () const;
        void setRadius (double r);

        Geometry::Point getPosition () const;
        void setPosition (Geometry::Point const &p);

        double getAngle () const { return 0; }
        void setAngle (double) {}

        /*--------------------------------------------------------------------------*/

        double calculateInertia (double mass) const;
        virtual void parentCallback (IModel *m);

private:

        double radius;
        Geometry::Point position;

};

} /* namespace Model */

#	endif /* CIRCLE_H_ */
