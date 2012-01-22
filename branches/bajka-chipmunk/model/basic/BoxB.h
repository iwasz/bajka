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

class BoxB : public AbstractModel {
public:

        C__ (void)
        b_ ("AbstractModel")

        BoxB () : angle (0), scale (0) {}
        virtual ~BoxB () {}

        virtual Geometry::Point getPosition () const { return box.ll; }
        virtual void setPosition (Geometry::Point const &p);

        virtual double getAngle () const { return angle; }
        virtual void setAngle (double a) { angle = a; }

        virtual double getSacle () const { return scale; }
        virtual void setScale (double s) { scale = s; }

/*--------------------------------------------------------------------------*/

        virtual IModel *findChild (Geometry::Point const &p);
        virtual Geometry::Box getBoundingBox () const { return box; }
        virtual bool inside (Geometry::Point const &p) const;

private:

        Geometry::Box box;
        double angle;
        double scale;

        E_ (BoxB)
};

} /* namespace Model */

#	endif /* BOXB_H_ */
