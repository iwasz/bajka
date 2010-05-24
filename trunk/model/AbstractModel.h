/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTMODEL_H_
#define ABSTRACTMODEL_H_

#include "IModel.h"
#include "geometry/Point.h"

// TODO Usunąć, tylko dla Box.
#include "geometry/Box.h"

namespace Model {

class AbstractModel : public IModel {
public:
        __d

        AbstractModel ();
        virtual ~AbstractModel () {}

/*------affine-transformations----------------------------------------------*/

        _m (setMove) void setMove (const Geometry::Point &p);
        void setRotate (double r);
        void setResize (double w, double h);
//        void resetMatrix ();

        Geometry::AffineMatrix const &
        getMatrix () const { return matrix; }

/*------dimensions----------------------------------------------------------*/

        virtual double getWidth () const = 0;
        virtual double getHeight () const = 0;

private:

        // Relative to root-element
        Geometry::AffineMatrix matrix;

        _e (AbstractModel)
};

/**
 *
 */
class Box : public AbstractModel, public Geometry::Box {
public:
        __c (void)
        _b ("AbstractModel", "Box")

        Box () : AbstractModel (), Geometry::Box () {}
        Box (double a, double b, double c, double d) : AbstractModel (), Geometry::Box (a, b, c, d) {}
        virtual ~Box () {}

/*--------------------------------------------------------------------------*/

        bool enclose (const Geometry::Point &p) const;

/*--------------------------------------------------------------------------*/

        virtual double getWidth () const { return getX2() - getX1 (); }
        void setWidth (double d) { setX2 (getX1 () + d); }

        virtual double getHeight () const { return getY2 () - getY1 (); }
        void setHeight (double d) { setY2 (getY1 () + d); }

        _e (Model::Box)
};

} // namespace

#	endif /* ABSTRACTMODEL_H_ */
