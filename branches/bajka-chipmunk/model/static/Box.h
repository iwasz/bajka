/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEDL_BOXB_H_
#define BAJKA_MODEDL_BOXB_H_

#include "../AbstractModel.h"

namespace Model {

class Box : public AbstractModel {
public:

        C__ (void)
        b_ ("AbstractModel")

        virtual ~Box () {}

/*--------------------------------------------------------------------------*/

        double getWidth () const { return box.getWidth (); }
        double getHeight () const { return box.getHeight (); }

        Geometry::Box const &getBox () const { return box; }
        m_ (setBox) void setBox (Geometry::Box const &b) { box = b; }

/*--------------------------------------------------------------------------*/

        Geometry::Point computeCenter () const;
        virtual IModel *findContains (Geometry::Point const &p);
        virtual Geometry::Box getBoundingBox () const;
        virtual bool contains (Geometry::Point const &p) const;
//        virtual void transform (Geometry::Point *p) const;

protected:

        Geometry::Box box;

        E_ (Box)
};

} /* namespace Model */

#	endif /* BOXB_H_ */
