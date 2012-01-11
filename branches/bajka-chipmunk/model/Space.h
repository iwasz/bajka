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

        Space ();
        virtual ~Space ();

        static cpSpace *getSpace () { return space; }

/*--------------------------------------------------------------------------*/

        Geometry::Point getPosition () const { return Geometry::Point (); }
        void setPosition (Geometry::Point const &position) { throw Util::OperationNotSupportedException ();  }

        double getAngle () const { return 0; }
        void setAngle (double a) { throw Util::OperationNotSupportedException ();  }

/*--------------------------------------------------------------------------*/

        Geometry::Point getGravity () const;
        void setGravity (Geometry::Point const &g);

private:

        static cpSpace *space;

};

} /* namespace Model */

#	endif /* SPACE_H_ */