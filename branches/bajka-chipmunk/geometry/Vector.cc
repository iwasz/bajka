/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <sstream>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include "Vector.h"

namespace Geometry {

std::ostream &operator<< (std::ostream &o, Geometry::Vector const &p)
{
        o << p.toString ();
        return o;
}

/****************************************************************************/

std::string Vector::toString () const
{
        std::ostringstream o;
        o << "Point (" << x << ", " << y << ")";
        return o.str ();
}

} /* namespace Geometry */
