/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "MotionEvent.h"

namespace Event {

MotionPointer::MotionPointer () :
        x (0),
        y (0),
        offsetX (0),
        offsety (0),
        pressure (0),
        size (0)
{
}

/****************************************************************************/

MotionEvent::MotionEvent () :
        position (Geometry::ZERO_POINT),
        metaState (0),
        pointerCount (0),
        buttons (0)
{
}

/****************************************************************************/

MotionPointer const &MotionEvent::getPointer (unsigned int i) const
{
        assert (i < MAX_POINTERS);
        return &pointers[i];
}

} // namespace Event
