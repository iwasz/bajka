/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MODEL_BOX_H_
#define MODEL_BOX_H_

#include "geometry/Box.h"
#include "Shape.h"

namespace Model {

/**
 * Model reprezentujący pudełko. Może służyć jako model do prostokąta, albo
 * do jakiegoś innego prostokątnego cudaka.
 * \ingroup Model
 */
class Box : public Shape, public Geometry::Box {
public:
        __c (void)
        _b ("AbstractModel", "Box")

        Box () : Shape (), Geometry::Box () {}
        Box (double a, double b, double c, double d) : Shape (), Geometry::Box (a, b, c, d) {}
        virtual ~Box () {}

/*--------------------------------------------------------------------------*/

//        bool enclose (const Geometry::Point &p) const;

//        const Geometry::Box &toScreenCoords () const { updateScreenCoords (); return screenCoords; }

/*--------------------------------------------------------------------------*/

//        virtual double getWidth () const { return getX2() - getX1 (); }
        void setWidth (double d) { setX2 (getX1 () + d); }

//        virtual double getHeight () const { return getY2 () - getY1 (); }
        void setHeight (double d) { setY2 (getY1 () + d); }

        virtual Geometry::Box const &getBoundingBox () const { return *this; }

private:

//        // TODO Test
//        void updateScreenCoords () const;
//        mutable Geometry::Box screenCoords;

        _e (Model::Box)
};

} // namespace

#	endif /* ABSTRACTMODEL_H_ */
