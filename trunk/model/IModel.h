/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMODEL_H_
#define IMODEL_H_

#include <Object.h>
#include "geometry/Utils.h"
#include "geometry/Point.h"

namespace Model {

/**
 * Marker
 * TODO Zastanowić się jakie właściwie tu powinny być metody.
 */
struct IModel : virtual public Core::Object {
        virtual ~IModel () {}

        /**
         * Returns affine transformation matrix for this object.
         */
        virtual
        Geometry::AffineMatrix const &
        getMatrix () const = 0;

        /**
         * Sprawdza, czy punkt znajduje się w środku danego modelu.
         */
        virtual bool enclose (const Geometry::Point &p) const = 0;
        //virtual bool enclose (const Geometry::Box &p) const = 0;
        // ...

        virtual void setMove (const Geometry::Point &p) = 0;
        virtual void setRotate (double r) = 0;
        virtual void setResize (double w, double h) = 0;
        virtual void setResizeW (double w) = 0;
        virtual void setResizeH (double h) = 0;

        virtual double getWidth () const = 0;
        virtual double getHeight () const = 0;
};

}

#	endif /* IMODEL_H_ */
