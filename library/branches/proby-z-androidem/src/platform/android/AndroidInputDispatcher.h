/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID
#ifndef BAJKA_ANDROIDINPUTDISPATCHER_H_
#define BAJKA_ANDROIDINPUTDISPATCHER_H_
#include "AbstractEventDispatcher.h"

namespace Event {

class AndroidInputDispatcher : public AbstractEventDispatcher {
public:

        virtual ~AndroidInputDispatcher () {}
        bool pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex);
        bool dispatch (Model::IModel *m, EventIndex const &modeliIndex, PointerInsideIndex *pointerInsideIndex, void *platformDependentData);
        void reset ();

protected:

        virtual IEvent *translate (void *platformDependentEvent);

};

} /* namespace Event */
#endif /* ANDROIDINPUTDISPATCHER_H_ */
#endif
