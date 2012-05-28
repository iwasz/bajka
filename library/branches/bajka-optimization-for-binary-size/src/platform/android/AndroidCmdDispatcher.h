/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID
#ifndef ANDROIDCMDDISPATCHER_H_
#define ANDROIDCMDDISPATCHER_H_
#include "AbstractEventDispatcher.h"

namespace Event {


class AndroidCmdDispatcher : public AbstractEventDispatcher {
public:

        virtual ~AndroidCmdDispatcher () {}

        bool pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex);
        bool dispatch (Model::IModel *m, EventIndex const &modeliIndex, PointerInsideIndex *pointerInsideIndex, void *platformDependentData);
        void reset ();

protected:

        IEvent *translate (void *platformDependentEvent);

};

} /* namespace Event */

#endif /* ANDROIDCMDDISPATCHER_H_ */
#endif
