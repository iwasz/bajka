/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LineString.h"

namespace Geometry {

Ptr <LineString> stringToLineString (std::string const &s)
{
        Ptr <LineString> ret = boost::make_shared <LineString> ();
        ret->push_back (makePoint (0, 0));
        ret->push_back (makePoint (40, 40));
        ret->push_back (makePoint (40, -40));
        ret->push_back (makePoint (-40, -40));
        ret->push_back (makePoint (-40, 40));
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
