/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <android/input.h>
#include "AndroidInputDispatcher.h"
#include "Functions.h"

namespace Event {

bool AndroidInputDispatcher::run (Model::IModel *m, EventIndex const &modeliIndex, PointerInsideIndex *pointerInsideIndex, void *platformDependentData)
{
        AInputEvent *androidEvent = static_cast <AInputEvent *> (platformDependentData);

        if (AInputEvent_getType (androidEvent) == AINPUT_EVENT_TYPE_MOTION) {
            float x = AMotionEvent_getX (androidEvent, 0);
            float y = AMotionEvent_getY (androidEvent, 0);

            LOGI ("Motion : %f, %f", x, y);
        }

        return true;
}

void AndroidInputDispatcher::reset ()
{

}

} /* namespace Event */
