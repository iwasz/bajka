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
        size (0),
        id (0)
{
}

/****************************************************************************/

MotionEvent::MotionEvent () :
        metaState (MOD_NONE),
        pointerCount (0),
        buttons (0),
        source (OTHER)
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

/****************************************************************************/

std::string MotionEvent::toString () const
{
        std::string buf = "pCnt=" + boost::lexical_cast <std::string> (pointerCount) + " ";

        for (int i = 0; i < pointerCount; ++i) {

                MotionPointer const &pointer = getPointer (i);

                buf += boost::lexical_cast <std::string> (pointer.id) + "=[" +
                                boost::lexical_cast <std::string> (pointer.position.x) + "," +
                                boost::lexical_cast <std::string> (pointer.position.y) + "," +
                                boost::lexical_cast <std::string> (pointer.pressure) + "," +
                                boost::lexical_cast <std::string> (pointer.size) + "] ";
        }

        return buf;
}

} // namespace Event
