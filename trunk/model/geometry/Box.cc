/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <sstream>
#include <boost/geometry/util/write_dsv.hpp>

#include "Box.h"

namespace Model2 {
using namespace boost::geometry;

/****************************************************************************/

Core::String Box::toString (unsigned int) const
{
        std::ostringstream o;
        o << "Box " << boost::geometry::dsv (*this);
        return o.str ();
}

} // names
