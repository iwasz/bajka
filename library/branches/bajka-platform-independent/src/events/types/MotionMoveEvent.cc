/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MotionMoveEvent.h"

namespace Event {

std::string MotionMoveEvent::toString () const
{
//        return "MotionMoveEvent (position=" + Geometry::toString (position) +
//                        ", movement=" + Geometry::toString (movement) +
//                        ", buttons=" + boost::lexical_cast <std::string> (buttons)+ ")";
        return "MotionMoveEvent";
}

} // namespace Event
