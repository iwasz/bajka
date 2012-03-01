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
#include "../IBox.h"

namespace Model {

class Box : public IBox, public AbstractModel {
public:

        C__ (void)
        b_ ("AbstractModel")

        virtual ~Box () {}

/*--------------------------------------------------------------------------*/

        double getWidth () const { return box.getWidth (); }
        void setWidth (double w) { box.setWidth (w); }
        double getHeight () const { return box.getHeight (); }
        void setHeight (double h) { box.setHeight (h); }

        Geometry::Box getBox () const { return box; }
        m_ (setBox) void setBox (Geometry::Box const &b) { box = b; }

        bool isBox () const { return true; }

/*--------------------------------------------------------------------------*/
        m_ (getView) View::IView *getView () { return AbstractModel::getView (); }
//        S_ (setView) void setView (View::IView *v) { AbstractModel::setView (v); }
        Geometry::Point computeCenter () const;
        virtual Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        virtual bool contains (Geometry::Point const &p) const;

protected:

        Geometry::Box box;

        E_ (Box)
};

} /* namespace Model */

#	endif /* BOXB_H_ */
