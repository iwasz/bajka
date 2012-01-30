/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEDL_CIRCLE_STATIC_H_
#define BAJKA_MODEDL_CIRCLE_STATIC_H_

#include "../AbstractModel.h"

namespace Model {

class Circle : public AbstractModel {
public:

        C__ (void)
        b_ ("AbstractModel")

        Circle () : radius (0) {}
        virtual ~Circle () {}

/*--------------------------------------------------------------------------*/

        Geometry::Point computeCenter () const;

        virtual double getRadius () const { return radius; }
        m_ (setRadius) virtual void setRadius (double r) { radius = r; }

/*--------------------------------------------------------------------------*/

        virtual IModel *findContains (Geometry::Point const &p);
        virtual Geometry::Box getBoundingBox () const;
        virtual bool contains (Geometry::Point const &p) const;
        virtual void transform (Geometry::Point *p) const;

protected:

        double radius;

        E_ (Circle)
};

} /* namespace Model */

#	endif /* BOXB_H_ */
