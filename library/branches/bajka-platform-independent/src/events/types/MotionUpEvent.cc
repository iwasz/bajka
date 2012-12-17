/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MotionUpEvent.h"

namespace Event {

std::string MotionUpEvent::toString () const
{
//        return "MotionUpEvent (position=" + Geometry::toString (position) + ", button=" + boost::lexical_cast <std::string> (button)+ ")";
        return "MotionUpEvent";
}

} /* namespace Event1 */
