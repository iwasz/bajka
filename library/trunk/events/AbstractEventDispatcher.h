/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACT_EVENTDISPATCHER_H_
#define ABSTRACT_EVENTDISPATCHER_H_

#include "ReflectionMacros.h"
#include "IDispatcher.h"
#include "App.h"
#include "types/Types.h"

namespace Event {

/**
 * Wspólna implemntacja dla różncyh platform.
 * \ingroup Events
 */
class AbstractEventDispatcher : public IDispatcher {
public:
        C__ (void)

        AbstractEventDispatcher () : app (NULL) {}
        virtual ~AbstractEventDispatcher () {}

        /**
         * Pobiera kolejne eventy z systemu i przekazuje je do dispatch.
         */
        virtual void pollAndDispatch (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex) = 0;

        /**
         * Konweruje event systemowy na event zrozumiały dla bajki i rozprowadza go po systemie.
         */
        void dispatch (Model::IModel *m, EventIndex const &modeliIndex, PointerInsideIndex *pointerInsideIndex, void *platformDependentEvent);

/*------getters-setters-----------------------------------------------------*/

        Util::App *getApp () { return app; }
        void setApp (Util::App *a) { app = a; }

protected:

        virtual IEvent *translate (void *platformDependentEvent) = 0;

private:

        void dispatchEventBackwards (Model::IModel *m, IEvent *e, PointerInsideIndex *pointerInsideIndex);

private:

        Util::App *app;

        E_ (AbstractEventDispatcher)
};

}

#endif /* EVENTDISPATCHER_H_ */
