/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTEVENTDISPATCHER_H_
#define ABSTRACTEVENTDISPATCHER_H_

#include "IDispatcher.h"
#include "types/Types.h"
#include "App.h"

namespace Event {

class AbstractEventDispatcher : public IDispatcher {
public:
        AbstractEventDispatcher () : app (NULL) {}
        virtual ~AbstractEventDispatcher () {}

        /**
         * Konweruje event systemowy na event zrozumiały dla bajki i rozprowadza go po systemie.
         */
        bool dispatch (Model::IModel *m, EventIndex const &modeliIndex, PointerInsideIndex *pointerInsideIndex, void *platformDependentEvent);

/*------getters-setters-----------------------------------------------------*/

        Util::App *getApp () { return app; }
        void setApp (Util::App *a) { app = a; }

protected:

        virtual IEvent *translate (void *platformDependentEvent) = 0;

private:

        void dispatchEventBackwards (Model::IModel *m, IEvent *e, PointerInsideIndex *pointerInsideIndex);

private:

        Util::App *app;
};

} /* namespace Event */

#endif /* ABSTRACTEVENTDISPATCHER_H_ */
