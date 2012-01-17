/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TimerEvent.h"
#include <boost/lexical_cast.hpp>

namespace Event {

std::string TimerEvent::toString () const
{
        return "TimerEvent (ticks=" + boost::lexical_cast <std::string> (ticks)+ ")";
}

} /* namespace Event1 */
