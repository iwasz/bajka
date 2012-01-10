/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHAPE_H_
#define SHAPE_H_

#include "AbstractModel.h"

namespace Model {

class Shape : public AbstractModel {
public:

        Shape () : shape (0) {}
        virtual ~Shape ();

        virtual double calculateInertia (double mass) const = 0;
        virtual void parentCallback (IModel *m);

        double const *getMatrix () const;

protected:

        cpShape *shape;

};

} /* namespace Model */

#	endif /* SHAPE_H_ */
