/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_BODY_H_
#define BAJKA_BODY_H_

#include "AbstractModel.h"

namespace Model {

class Body : public AbstractModel {
public:

        Body ();
        virtual ~Body () {}

        Geometry::Point getPosition () const;
        void setPosition (Geometry::Point const &position);

        double getAngle () const;
        void setAngle (double a);

        double const *getMatrix () const;

/*--------------------------------------------------------------------------*/

        double getMass () const;
        void setMass (double m);

        double getInertia () const;
        void setInertia (double i);
        void addInertia (double i);

        cpBody *getBody () { return body; }
        cpBody const *getBody () const { return body; }

private:

        cpBody *body;


};

} /* namespace Model */

#	endif /* BODY_H_ */
