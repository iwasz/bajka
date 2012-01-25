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

        BoxB () : angle (0), scale (1) {}
        virtual ~BoxB () {}

        virtual Geometry::Point getPosition () const { return position; }
        m_ (setPosition) virtual void setPosition (Geometry::Point const &p) { position = p; }

        virtual Geometry::Point getCenter () const { return center; }
        m_ (setCenter) virtual void setCenter (Geometry::Point const &p) { center = p; }

        virtual double getAngle () const { return angle; }
        m_ (setAngle) virtual void setAngle (double a) { angle = a; }

        virtual double getScale () const { return scale; }
        m_ (setScale) virtual void setScale (double s) { scale = s; }

/*--------------------------------------------------------------------------*/

        // Nie uwzględnia skali.
//        double getWidth () const { return box}
//        double getHeight () const {}

        // Tymczasowa?
        Geometry::Box const &getBox () const { return box; }
        m_ (setBox) void setBox (Geometry::Box const &b) { box = b; }

/*--------------------------------------------------------------------------*/

        virtual IModel *findChild (Geometry::Point const &p);
        virtual Geometry::Box getBoundingBox () const { return box; }
        virtual bool inside (Geometry::Point const &p) const;
        virtual void transform (Geometry::Point *p);

private:

        Geometry::Box box;
        Geometry::Point position;
        Geometry::Point center;
        double angle;
        double scale;

        E_ (BoxB)
};

} /* namespace Model */

#	endif /* BOXB_H_ */
