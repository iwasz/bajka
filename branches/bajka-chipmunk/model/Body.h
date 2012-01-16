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

        C__ (void)
        b_ ("AbstractModel")
        Body ();
        virtual ~Body ();

/*--------------------------------------------------------------------------*/

        virtual Geometry::Point getPosition () const;
        m_ (setPosition) virtual void setPosition (Geometry::Point const &position);

        virtual double getAngle () const;
        virtual void setAngle (double a);

/*--------------------------------------------------------------------------*/

        double getMass () const;
        m_ (setMass) void setMass (double m);

        double getInertia () const;
        void setInertia (double i);
        void addInertia (double i);

        cpBody *getBody () { return body; }
        cpBody const *getBody () const { return body; }

protected:

        Body (int) {}
        cpBody *body;

        E_ (Body)
};

} /* namespace Model */

#	endif /* BODY_H_ */
