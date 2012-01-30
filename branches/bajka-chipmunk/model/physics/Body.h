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
#include "../../util/Exceptions.h"

namespace Model {

class Body : public AbstractModel {
public:

        C__ (void)
        b_ ("AbstractModel")
        Body ();
        virtual ~Body ();

/*--------------------------------------------------------------------------*/

        /**
         * Body nie ma swojej pozycji, tylko ma przesunięcie i obrót.
         */
        Geometry::Point getTranslate () const;
        void setTranslate (Geometry::Point const &position);

        /**
         * Dlatego center wypada tam gdzie przesunięcie.
         */
        Geometry::Point computeCenter () const { return translate; }

        double getAngle () const;
        void setAngle (double a);

        double getScale () const { return 1; }
        void setScale (double s) { throw Util::OperationNotSupportedException (); }

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
