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

        Box () : angle (0), scale (1) {}
        virtual ~Box () {}

        virtual Geometry::Point getPosition () const { return position; }
        m_ (setPosition) virtual void setPosition (Geometry::Point const &p) { position = p; }

        virtual Geometry::Point getCenter () const { return center; }
        m_ (setCenter) virtual void setCenter (Geometry::Point const &p) { center = p; }

        virtual double getAngle () const { return angle; }
        m_ (setAngle) virtual void setAngle (double a) { angle = a; }

        virtual double getScale () const { return scale; }
        m_ (setScale) virtual void setScale (double s) { scale = s; }

/*--------------------------------------------------------------------------*/

        double getWidth () const { return box.getWidth (); }
        double getHeight () const { return box.getHeight (); }

        Geometry::Box const &getBox () const { return box; }
        m_ (setBox) void setBox (Geometry::Box const &b) { box = b; }

/*--------------------------------------------------------------------------*/

        virtual IModel *findContains (Geometry::Point const &p);
        virtual Geometry::Box getBoundingBox () const;
        virtual bool contains (Geometry::Point const &p) const;
        virtual void transform (Geometry::Point *p) const;

protected:

        Geometry::Box box;
        Geometry::Point position;
        Geometry::Point center;
        double angle;
        double scale;

        E_ (Box)
};

} /* namespace Model */

#	endif /* BOXB_H_ */
