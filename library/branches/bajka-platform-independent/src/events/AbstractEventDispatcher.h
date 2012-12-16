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

protected:

        /**
         * Zwraca true, kiedy event został obsłużony przez grę i nie powinien zostać przekazany do
         * systemu. Ma to znaczenie w androidzie, gdzie aplikacja i system współdzielą eventy.
         */
        bool dispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex, Event::IEvent *event);

        /**
         * Emituje w tył
         * @param breakChain Zwraca true jeśli ostatni handler eventu zwrócił BREAK, czli prosi o przerwanie łańcucha
         * wywołań.
         */
        bool dispatchEventBackwards (Model::IModel *m, IEvent *e, Event::PointerInsideIndex *pointerInsideIndex, bool *breakChain = NULL);
};

} /* namespace Event */
#endif /* ABSTRACTEVENTDISPATCHER_H_ */
