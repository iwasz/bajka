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
        position (Geometry::ZERO_POINT),
        movement (Geometry::ZERO_POINT),
        pressure (0),
        size (0)
{
}

/****************************************************************************/

MotionEvent::MotionEvent () :
        metaState (MOD_NONE),
        pointerCount (0),
        buttons (0)
{
}

/****************************************************************************/

MotionPointer const &MotionEvent::getPointer (unsigned int i) const
{
        assert (i < MAX_POINTERS);
        return pointers[i];
}

/****************************************************************************/

MotionPointer &MotionEvent::getPointer (unsigned int i)
{
        assert (i < MAX_POINTERS);
        return pointers[i];
}

} // namespace Event
