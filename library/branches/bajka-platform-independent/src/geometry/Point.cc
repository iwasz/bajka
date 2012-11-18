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
#include "Point3.h"
#include "util/Exceptions.h"

/****************************************************************************/

namespace Geometry {
using namespace boost;
using namespace boost::geometry;
using namespace boost::algorithm;


Point stringToPoint (std::string const &s)
{
        Point p;
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        tokenizer tok (s, boost::char_separator<char> (","));
        tokenizer::iterator i = tok.begin ();

        assertThrow (i != tok.end (), "stringToPoint : problem parsing string : [" + s + "]");
        p.x = lexical_cast<double> (trim_copy (*i++));

        assertThrow (i != tok.end (), "stringToPoint : problem parsing string : [" + s + "]");
        p.y = lexical_cast<double> (trim_copy (*i));

        return p;
}

/****************************************************************************/

Core::Variant stringToPointVariant (std::string const &p)
{
        return Core::Variant (stringToPoint (p));
}

/****************************************************************************/

Point3 stringToPoint3 (std::string const &s)
{
        Point3 p;
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        tokenizer tok (s, boost::char_separator<char> (","));
        tokenizer::iterator i = tok.begin ();

        assertThrow (i != tok.end (), "stringToPoint : problem parsing string : [" + s + "]");
        p.x = lexical_cast<double> (trim_copy (*i++));

        assertThrow (i != tok.end (), "stringToPoint : problem parsing string : [" + s + "]");
        p.y = lexical_cast<double> (trim_copy (*i++));

        assertThrow (i != tok.end (), "stringToPoint : problem parsing string : [" + s + "]");
        p.z = lexical_cast<double> (trim_copy (*i));

        return p;
}

/****************************************************************************/

Core::Variant stringToPoint3Variant (std::string const &p)
{
        return Core::Variant (stringToPoint3 (p));

}

/****************************************************************************/

std::ostream &operator<< (std::ostream &o, Geometry::Point const &p)
{
        o << "Point (" << p.x << ", " << p.y << ")";
        return o;
}

/****************************************************************************/

std::string toString (Geometry::Point const &p)
{
        std::ostringstream o;
        o << "Point (" << p.x << ", " << p.y << ")";
        return o.str ();
}

/****************************************************************************/

Point operator+ (Point const &a, Point const &b)
{
        Point ret = { a.x + b.x, a.y + b.y };
        return ret;
}

} // nam
