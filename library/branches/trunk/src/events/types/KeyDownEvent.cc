/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "KeyDownEvent.h"
#include <boost/lexical_cast.hpp>

namespace Event {

std::string KeyDownEvent::toString () const
{
        return "KeyDownEvent (code=" + boost::lexical_cast <std::string> (keyCode) + ", mod=" + boost::lexical_cast <std::string> (keyMod) + ")";
}

} /* namespace Event */
