/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <android/input.h>
#include "AndroidInputDispatcher.h"
#include "Logging.h"

namespace Event {

bool AndroidInputDispatcher::pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex)
{

}

bool AndroidInputDispatcher::dispatch (Model::IModel *m, EventIndex const &modeliIndex, PointerInsideIndex *pointerInsideIndex, void *platformDependentData)
{
        AInputEvent *androidEvent = static_cast <AInputEvent *> (platformDependentData);
        logEvent (androidEvent);
        return true;
}

void AndroidInputDispatcher::reset ()
{

}

IEvent *AndroidInputDispatcher::translate (void *platformDependentEvent)
{
        return NULL;
}

} /* namespace Event */
