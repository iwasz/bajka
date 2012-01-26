/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_CIRCLE_H_
#define BAJKA_CIRCLE_H_

#include "../geometry/Point.h"
#include "Shape.h"
#include "../AbstractModel.h"

namespace Model {

class Circle /*: public Shape*/, public AbstractModel {
public:

        C__ (void)
        b_ ("AbstractModel", "Shape")

        virtual ~Circle () {}

        virtual void setPosition (Geometry::Point const &p);
        virtual Geometry::Point getPosition () const;

        double getRadius () const;
        m_ (setRadius) void setRadius (double r);

        double getAngle () const { return 0; }
        m_ (setAngle) void setAngle (double) {}

/*--------------------------------------------------------------------------*/

        virtual void parentCallback (IModel *m);

private:

        double radius;
        Geometry::Point position;

        E_ (Model::Circle)

};

} /* namespace Model */

#	endif /* CIRCLE_H_ */
