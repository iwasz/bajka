/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <boost/geometry/util/write_dsv.hpp>
#include "LineString.h"

namespace Model2 {
using namespace boost::geometry;

/****************************************************************************/

Core::String LineString::toString (unsigned int) const
{
        std::ostringstream o;
        o << "LineString " << boost::geometry::dsv (*this);
        return o.str ();
}
}
