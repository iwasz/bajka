/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <sstream>
#include "Box.h"

namespace Geometry {

/****************************************************************************/

std::string Box::toString () const
{
        std::ostringstream o;
        o << "Box (" << ll << ", " << ur << ")";
        return o.str ();
}

} // names
