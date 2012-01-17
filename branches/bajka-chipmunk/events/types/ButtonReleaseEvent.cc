/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ButtonReleaseEvent.h"

namespace Event {

std::string ButtonReleaseEvent::toString () const
{
        return "ButtonReleaseEvent (position=" + position.toString () + ", button=" + boost::lexical_cast <std::string> (button)+ ")";
}

} /* namespace Event1 */
