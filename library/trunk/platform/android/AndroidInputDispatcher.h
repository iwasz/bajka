/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANDROIDINPUTDISPATCHER_H_
#define ANDROIDINPUTDISPATCHER_H_
#include "AbstractEventDispatcher.h"

namespace Event {

class AndroidInputDispatcher : public AbstractEventDispatcher {
public:

        virtual ~AndroidInputDispatcher () {}
        bool run (Model::IModel *m, EventIndex const &modeliIndex, PointerInsideIndex *pointerInsideIndex, void *platformDependentData);
        void reset ();

        Util::App *getApp () {}
        void setApp (Util::App *a) {}

};

} /* namespace Event */
#endif /* ANDROIDINPUTDISPATCHER_H_ */
