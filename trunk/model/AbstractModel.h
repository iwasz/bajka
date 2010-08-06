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

        _m (setMove) virtual void setMove (const Geometry::Point &p);
        _m (setRotate) virtual void setRotate (double r);
        virtual void setResize (double w, double h);
        _m (setResizeW) virtual void setResizeW (double w) { setResize (w, 1); }
        _m (setResizeH) virtual void setResizeH (double h) { setResize (1, h); }

        virtual Geometry::AffineMatrix const &
        getMatrix () const { return matrix; }

/*------dimensions----------------------------------------------------------*/

//        virtual double getWidth () const = 0;
//        virtual double getHeight () const = 0;

protected:

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

        const Geometry::Box &toScreenCoords () const { updateScreenCoords (); return screenCoords; }

/*--------------------------------------------------------------------------*/

        virtual double getWidth () const { return getX2() - getX1 (); }
        void setWidth (double d) { setX2 (getX1 () + d); }

        virtual double getHeight () const { return getY2 () - getY1 (); }
        void setHeight (double d) { setY2 (getY1 () + d); }

private:

        // TODO Test
        void updateScreenCoords () const;
        mutable Geometry::Box screenCoords;

        _e (Model::Box)
};

} // namespace

#	endif /* ABSTRACTMODEL_H_ */
