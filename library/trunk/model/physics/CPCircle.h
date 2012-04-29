/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#ifndef BAJKA_PHYS_CIRCLE_H_
#define BAJKA_PHYS_CIRCLE_H_

#include "../geometry/Point.h"
#include "../static/Circle.h"
#include "Shape.h"
#include "../../util/Exceptions.h"

namespace Model {

class CPCircle : public Circle, public Shape {
public:

        C__ (void)
        b_ ("Circle", "Shape")

        virtual ~CPCircle () {}

/*--------------------------------------------------------------------------*/

        Geometry::Point getOrigin () const;
        void setOrigin (Geometry::Point const &p);

        double getRadius () const;
        void setRadius (double r);

/*--------------------------------------------------------------------------*/

        // Szejpów chipmunkowych nie można zmieniać i nie można transformowac. Tylko body można.
        Geometry::Point getTranslate () const { return Geometry::Point (); }
        void setTranslate (Geometry::Point const &p) { throw Util::OperationNotSupportedException (); }

        void setCenter (Geometry::Point const &p) { throw Util::OperationNotSupportedException (); }

        double getAngle () const { return 0; }
        virtual void setAngle (double a) { throw Util::OperationNotSupportedException (); }

        double getScale () const { return 1; }
        virtual void setScale (double s) { throw Util::OperationNotSupportedException (); }

/*--------------------------------------------------------------------------*/

        virtual void onParentSet (IModel *m);
        virtual Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;

private:

        double radius;
        Geometry::Point position;

        E_ (CPCircle)

};

} /* namespace Model */

#endif /* CIRCLE_H_ */
#endif
