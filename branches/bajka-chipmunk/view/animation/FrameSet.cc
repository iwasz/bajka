/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANDROID
#include "FrameSet.h"

namespace View {

bool FrameSet::inc ()
{
        ++current;

        if (current == frames.end ()) {
                current = frames.begin ();
                return true;
        }

        return false;
}

/****************************************************************************/

bool FrameSet::dec ()
{
        if (current == frames.begin ()) {
                current = frames.end ();
                --current;
                return true;
        }

        return false;
}

/****************************************************************************/

void FrameSet::reset ()
{
        current = frames.begin ();
}

/****************************************************************************/

void FrameSet::setFrames (Util::IntVector const &f)
{
        frames = f;
        reset ();
}

} /* namespace View */
#endif
