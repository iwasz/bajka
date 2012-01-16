/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <sstream>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>
#include "Point.h"


/****************************************************************************/

namespace Geometry {
using namespace boost::geometry;
using namespace boost;
using namespace boost::algorithm;

Point::Point (std::string const &s)
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    
    tokenizer tok (s, boost::char_separator<char> (","));
    
    tokenizer::iterator i = tok.begin ();
    
    try {
	assert (i != tok.end ());
	x = lexical_cast <double> (trim_copy (*i++));
        
	assert (i != tok.end ());
	y = lexical_cast <double> (trim_copy (*i));
    }
    catch (boost::bad_lexical_cast const &e) {
	assert (0);
    }
}

/****************************************************************************/

std::ostream &operator<< (std::ostream &o, Geometry::Point const &p)
{
        o << p.toString ();
        return o;
}

/****************************************************************************/

std::string Point::toString () const
{
        std::ostringstream o;
        o << "Point (" << x << ", " << y << ")";
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

/****************************************************************************/

double Point::distance () const
{
	return boost::geometry::distance (Point (), *this);
}

/****************************************************************************/

double Point::distance (Point const &p) const
{
	return boost::geometry::distance (p, *this);
}

} // nam
