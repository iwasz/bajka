/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ButtonPressEvent.h"

namespace Event {

std::string ButtonPressEvent::toString () const
{
        return "ButtonPressEvent (position=" + position.toString () + ", button=" + boost::lexical_cast <std::string> (button)+ ")";
}

} /* namespace Event1 */
