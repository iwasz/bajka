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
#include "../static/Box.h"
#include "../../util/Exceptions.h"

namespace Model {

class CPBox : public Box, public Shape {
public:

        C__ (void)
        b_ ("Box", "Shape")

        CPBox () : Box (), Shape () {}
        virtual ~CPBox () {}

/*--------------------------------------------------------------------------*/

        // Szejpów chipmunkowych nie można zmieniać i nie można transformowac. Tylko body można.
        Geometry::Point getPosition () const { throw Util::OperationNotSupportedException (); }
        void setPosition (Geometry::Point const &p) { throw Util::OperationNotSupportedException (); }

        Geometry::Point getCenter () const { throw Util::OperationNotSupportedException (); }
        void setCenter (Geometry::Point const &p) { throw Util::OperationNotSupportedException (); }

        double getAngle () const { throw Util::OperationNotSupportedException (); }
        virtual void setAngle (double a) { throw Util::OperationNotSupportedException (); }

        double getScale () const { throw Util::OperationNotSupportedException (); }
        virtual void setScale (double s) { throw Util::OperationNotSupportedException (); }

/*--------------------------------------------------------------------------*/

        void parentCallback (IModel *m);

        E_ (CPBox)
};

} /* namespace Model1 */

#	endif /* BOX_H_ */
