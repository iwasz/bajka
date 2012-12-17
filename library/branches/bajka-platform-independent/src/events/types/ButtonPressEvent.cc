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
//        return "ButtonPressEvent (position=" + Geometry::toString (position) + ", button=" + boost::lexical_cast <std::string> (button)+ ")";
        return "ButtonPressEvent";
}

} /* namespace Event1 */
