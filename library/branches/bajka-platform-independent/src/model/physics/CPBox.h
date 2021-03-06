/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_CHIPMUNK
#ifndef BAJKA_PHYS_BOX_H_
#define BAJKA_PHYS_BOX_H_

#include "geometry/AffineMatrix.h"
#include "geometry/Point.h"
#include "Shape.h"
#include "model/static/Box.h"
#include "util/Exceptions.h"

namespace Model {

class CPBox : public Box, public Shape {
public:

        C__ (void)
        b_ ("Box", "Shape")

        CPBox () : Box (), Shape () {}
        virtual ~CPBox () {}

/*--------------------------------------------------------------------------*/

        // Szejpów chipmunkowych nie można zmieniać i nie można transformowac. Tylko body można.
        Geometry::Point getTranslate () const;
        void setTranslate (Geometry::Point const &p) { throw Util::OperationNotSupportedException (); }

        Geometry::Point getRotationCenter () const;
        void setRotationCenter (Geometry::Point const &p) { throw Util::OperationNotSupportedException (); }

        double getAngle () const { return 0; }
        virtual void setAngle (double a) { throw Util::OperationNotSupportedException (); }

        double getScale () const { return 1; }
        virtual void setScale (double s) { throw Util::OperationNotSupportedException (); }

/*--------------------------------------------------------------------------*/

        void onParentSet (IModel *m);

        E_ (CPBox)
};

} /* namespace Model1 */

#endif /* BOX_H_ */
#endif
