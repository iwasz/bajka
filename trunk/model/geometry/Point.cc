/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <sstream>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/util/write_dsv.hpp>

#include "Point.h"

namespace Geometry {
using namespace boost::geometry;

/****************************************************************************/

Core::String Point::toString (unsigned int) const
{
        std::ostringstream o;
        o << "Point " << boost::geometry::dsv (*this);
        return o.str ();
}

/****************************************************************************/

Point &Point::operator+= (const Point &p)
{
        add_point (*this, p);
        return *this;
}

/****************************************************************************/

Point &Point::operator-= (const Point &p)
{
        subtract_point (*this, p);
        return *this;
}

/****************************************************************************/

Point &Point::operator*= (const Point &p)
{
        multiply_point (*this, p);
        return *this;
}

/****************************************************************************/

Point &Point::operator/= (const Point &p)
{
        divide_point (*this, p);
        return *this;
}

/****************************************************************************/

Point &Point::operator+= (double d)
{
        add_value (*this, d);
        return *this;
}

/****************************************************************************/

Point &Point::operator-= (double d)
{
        subtract_value (*this, d);
        return *this;
}

/****************************************************************************/

Point &Point::operator*= (double d)
{
        multiply_value (*this, d);
        return *this;
}

/****************************************************************************/

Point &Point::operator/= (double d)
{
        divide_value (*this, d);
        return *this;
}

} // nam
