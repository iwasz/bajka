/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LineString.h"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include "../util/Exceptions.h"

namespace Geometry {
using namespace boost::geometry;
using namespace boost;
using namespace boost::algorithm;

Ptr <LineString> stringToLineString (std::string const &s)
{
        Ptr <LineString> ret = boost::make_shared <LineString> ();

        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        tokenizer tok (s, boost::char_separator<char> (" "));

        Point pen = {0, 0};
        Point first = {0, 0};
        bool firstSet = false;
        std::string command;
        int pointNumber = 0;

        for (tokenizer::iterator i = tok.begin (); i != tok.end (); ++i) {
                std::string token = *i;
                bool firstCommand = (i == tok.begin ());

                if (is_any_of ("mMlLzZcC") (token[0])) {
                        if (token == "z" || token == "Z") {
                                ret->push_back (first);
                                break;
                        }

                        command = token;
                }
                else {
                        Point p = stringToPoint (token);

                        if (!firstSet) {
                                first = p;
                                firstSet = true;
                        }

                        if (command == "m") {
                                add_point (pen, p);
                                command = "l";
                                ret->push_back (pen);
                        }
                        else if (command == "M") {
                                pen = p;
                                // TODO multi-path nie będzie teraz obsługiwny.
                                command = (firstCommand) ? ("l") : ("L");
                                ret->push_back (pen);
                        }
                        else if (command == "l") {
                                add_point (pen, p);
                                ret->push_back (pen);
                        }
                        else if (command == "L") {
                                ret->push_back (p);
                        }
                        // Bezier rysowany jako zwykły odcinek.
                        else if (command == "c" || command == "C") {
                                if (pointNumber++ >= 2) {
                                        ret->push_back ((command == "c") ? pen : p);
                                        pointNumber = 0;
                                }
                        }
                }
        }

        return ret;

}

/**
 * Tworzy punkt z reprezentacji napisowej, zwraca jako Core::Variant.
 */
Core::Variant stringToLineStringVariant (std::string const &p)
{
        return Core::Variant (stringToLineString (p));
}


} /* namespace Geometry */
