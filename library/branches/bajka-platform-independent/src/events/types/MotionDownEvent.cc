/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MotionDownEvent.h"

namespace Event {

std::string MotionDownEvent::toString () const
{
//        return "MotionDownEvent (position=" + Geometry::toString (position) + ", button=" + boost::lexical_cast <std::string> (button)+ ")";
        return "MotionDownEvent";
}

} /* namespace Event1 */
