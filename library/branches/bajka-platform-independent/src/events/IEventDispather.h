/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IEVENTDISPATHER_H_
#define IEVENTDISPATHER_H_

namespace Model {
struct IModel;
}

namespace View {
class GLContext;
}

namespace Event {
class IEvent;
class PointerInsideIndex;
class EventIndex;

/**
 *
 */
class IEventDispather {
public:
        virtual ~IEventDispather () {}

        /**
         *
         */
        virtual bool pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex, View::GLContext const *ctx) = 0;

        /**
         * Zwraca true, kiedy event został obsłużony przez grę i nie powinien zostać przekazany do
         * systemu. Ma to znaczenie w androidzie, gdzie aplikacja i system współdzielą eventy.
         */
        virtual bool dispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex, Event::IEvent *event) = 0;

        /**
         *
         */
        virtual bool dispatchEventBackwards (Model::IModel *m, IEvent *e, Event::PointerInsideIndex *pointerInsideIndex) = 0;

};

} /* namespace Event */
#endif /* IEVENTDISPATHER_H_ */
