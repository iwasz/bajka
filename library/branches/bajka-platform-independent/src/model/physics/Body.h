/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#ifndef BAJKA_BODY_H_
#define BAJKA_BODY_H_

#include "util/Exceptions.h"
#include "model/Group.h"

struct cpBody;

namespace Model {

class Body : public Group {
public:

        C__ (void)
        b_ ("Group")
        Body ();
        virtual ~Body ();

/*--------------------------------------------------------------------------*/

        /**
         * Body nie ma swojej pozycji, tylko ma przesunięcie i obrót.
         */
        Geometry::Point getTranslate () const;
        void setTranslate (Geometry::Point const &position);

        double getAngle () const;
        void setAngle (double a);

        double getScale () const { return 1; }
        void setScale (double s) { throw Util::OperationNotSupportedException (); }

        void setCenter (Geometry::Point const &p) { throw Util::OperationNotSupportedException (); }

/*--------------------------------------------------------------------------*/

        double getMass () const;
        m_ (setMass) void setMass (double m);

        double getInertia () const;
        void setInertia (double i);
        void addInertia (double i);

        cpBody *getBody () { return body; }
        cpBody const *getBody () const { return body; }

protected:

        Body (int) : body (NULL) {}
        cpBody *body;

        E_ (Body)
};

} /* namespace Model */

#endif /* BODY_H_ */
#endif
