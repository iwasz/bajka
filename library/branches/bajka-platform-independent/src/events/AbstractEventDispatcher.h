/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTEVENTDISPATCHER_H_
#define ABSTRACTEVENTDISPATCHER_H_

#include "IEventDispather.h"

namespace Event {

class AbstractEventDispatcher : public IEventDispather {
public:
        virtual ~AbstractEventDispatcher () {}

        virtual bool dispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex, Event::IEvent *event);
        virtual bool dispatchEventBackwards (Model::IModel *m, IEvent *e, Event::PointerInsideIndex *pointerInsideIndex);
};

} /* namespace Event */
#endif /* ABSTRACTEVENTDISPATCHER_H_ */
