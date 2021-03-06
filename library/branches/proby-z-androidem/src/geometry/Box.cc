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
#include "Box.h"
#include "../util/Exceptions.h"

namespace Geometry {
using namespace boost::geometry;
using namespace boost;
using namespace boost::algorithm;

const Box Box::ZERO_BOX;

/****************************************************************************/

Box::Box (std::string const &s)
{
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        tokenizer tok (s, boost::char_separator<char> (","));
        tokenizer::iterator i = tok.begin ();

        assertThrow (i != tok.end (), "Box::Box : problem parsing string : [" + s + "]");
        ll.x = lexical_cast <double> (trim_copy (*i++));

        assertThrow (i != tok.end (), "Box::Box : problem parsing string : [" + s + "]");
        ll.y = lexical_cast <double> (trim_copy (*i++));

        assertThrow (i != tok.end (), "Box::Box : problem parsing string : [" + s + "]");
        ur.x = lexical_cast <double> (trim_copy (*i++));

        assertThrow (i != tok.end (), "Box::Box : problem parsing string : [" + s + "]");
        ur.y = lexical_cast <double> (trim_copy (*i));
}

/****************************************************************************/

void Box::merge (Box const &b)
{
	ll.x = std::min (ll.x, b.ll.x);
	ll.y = std::min (ll.y, b.ll.y);
	ur.x = std::max (ur.x, b.ur.x);
	ur.y = std::max (ur.y, b.ur.y);
}

/****************************************************************************/

std::string toString (Box const &b)
{
        std::ostringstream o;
        o << "Box (" << b.ll << ", " << b.ur << ")";
        return o.str ();
}

} // names
