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

namespace Model2 {

class AbstractModel : public IModel {
public:
        __d

        AbstractModel ();
        virtual ~AbstractModel () {}

        _m (setMove) void setMove (const Point &p);
        void setRotate (double r);
        void setResize (double w, double h);
        void resetMatrix ();

//        AffineMatrix const &
//        getMatrix () const { return relative.UblasTransformer::matrix (); }

        AffineMatrix const &
        getMatrix () const { return matrix; }

private:

        // Relative to root-element
//        AffineTransformation relative;
        AffineMatrix matrix;

        _e (AbstractModel)
};

/*
 *
 */
class Box2 : public AbstractModel, public Model2::Box {
public:

        __c (void)
        _b ("AbstractModel", "Box")

        virtual ~Box2 () {}

//        Model2::Box const &getBox () const { return box; }
//        void setBox (Model2::Box const &box) { this->box = box; }
//
//private:
//
//        Model2::Box box;
        _e (Box2)
};

} // namespace

#	endif /* ABSTRACTMODEL_H_ */
