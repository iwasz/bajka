/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Padding.h"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include "util/Exceptions.h"

namespace Model {
using boost::lexical_cast;
using namespace boost::algorithm;

Padding::Padding (std::string const &s)
{
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        tokenizer tok (s, boost::char_separator<char> (","));
        tokenizer::iterator i = tok.begin ();

        assertThrow (i != tok.end (), "Box::Box : problem parsing string : [" + s + "]");
        top = lexical_cast <float> (trim_copy (*i++));

        assertThrow (i != tok.end (), "Box::Box : problem parsing string : [" + s + "]");
        right = lexical_cast <float> (trim_copy (*i++));

        assertThrow (i != tok.end (), "Box::Box : problem parsing string : [" + s + "]");
        bottom = lexical_cast <float> (trim_copy (*i++));

        assertThrow (i != tok.end (), "Box::Box : problem parsing string : [" + s + "]");
        left = lexical_cast <float> (trim_copy (*i));
}

} /* namespace Model */
