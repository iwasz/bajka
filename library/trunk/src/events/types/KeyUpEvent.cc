/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "KeyUpEvent.h"
#include <boost/lexical_cast.hpp>

namespace Event {

std::string KeyUpEvent::toString () const
{
        return "KeyUpEvent (code=" + boost::lexical_cast <std::string> (keyCode) + ", mod=" + boost::lexical_cast <std::string> (keyMod) + ")";
}

} /* namespace Event */
