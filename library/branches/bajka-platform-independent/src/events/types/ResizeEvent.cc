/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ResizeEvent.h"
#include <boost/lexical_cast.hpp>

namespace Event {

std::string ResizeEvent::toString () const
{
        return "ResizeEvent (width=" + boost::lexical_cast <std::string> (width) + ", height=" + boost::lexical_cast <std::string> (height) + ")";
}


} /* namespace Event */
