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
        return "MotionDownEvent " + MotionEvent::toString ();
}

} /* namespace Event1 */
