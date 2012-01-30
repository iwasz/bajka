/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SPACE_H_
#define BAJKA_SPACE_H_

#include "AbstractModel.h"
#include "../util/Exceptions.h"

namespace Model {

class Space : public AbstractModel {
public:

        C__ (void)
        b_ ("AbstractModel")

        Space ();
        virtual ~Space ();

        static cpSpace *getSpace () { return space; }

/*--------------------------------------------------------------------------*/

//        Czemu nie można? Można przecież - cała symulacja się przesunie, obróci etc.
//        Geometry::Point getTranslate () const { return Geometry::Point (); }
//        void setTranslate (Geometry::Point const &position) { throw Util::OperationNotSupportedException ();  }
//
//        double getAngle () const { return 0; }
//        void setAngle (double a) { throw Util::OperationNotSupportedException ();  }

        // W środku rodzica.
        virtual Geometry::Point computeCenter () const { return Geometry::Point (); }

/*--------------------------------------------------------------------------*/

        IModel *findContains (Geometry::Point const &p);

/*--------------------------------------------------------------------------*/

        Geometry::Point getGravity () const;
        m_ (setGravity) void setGravity (Geometry::Point const &g);

private:

        static cpSpace *space;

        E_ (Space)
};

} /* namespace Model */

#	endif /* SPACE_H_ */
