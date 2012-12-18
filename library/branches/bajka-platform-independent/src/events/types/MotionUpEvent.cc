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
        return "MotionUpEvent " + MotionEvent::toString ();
}

} /* namespace Event1 */
