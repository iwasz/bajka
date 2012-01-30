/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SEGMENT_H_
#define BAJKA_SEGMENT_H_

#include "../AbstractModel.h"

namespace Model {

class Line : public AbstractModel {
public:
//        C__ (void)
//        b_ ("AbstractModel")

        Line () {}
        Line (Geometry::Point const &la, Geometry::Point const &lb) : a (la), b (lb) {}
        virtual ~Line () {}

/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/

//        Geometry::Point computeCenter () const;
//        virtual IModel *findContains (Geometry::Point const &p);
//        virtual Geometry::Box getBoundingBox () const;
//        virtual bool contains (Geometry::Point const &p) const;

protected:

        Geometry::Point a, b;

//        E_ (Line)
};

} // namespace

#	endif /* SEGMENT_H_ */
