/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MouseMotionEvent.h"

namespace Event {

std::string MouseMotionEvent::toString () const
{
        return "MouseMotionEvent (position=" + Geometry::toString (position) +
                        ", movement=" + Geometry::toString (movement) +
                        ", buttons=" + boost::lexical_cast <std::string> (buttons)+ ")";
}

} // namespace Event
