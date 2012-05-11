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
#include "../../events/IDispatcher.h"

namespace Event {

class AndroidCmdDispatcher : public IDispatcher {
public:

        virtual ~AndroidCmdDispatcher () {}

        bool run (Model::IModel *m, EventIndex const &modeliIndex, PointerInsideIndex *pointerInsideIndex, void *platformDependentData);
        void reset ();

        Util::App *getApp () {}
        void setApp (Util::App *a) {}

};

} /* namespace Event */

#endif /* ANDROIDCMDDISPATCHER_H_ */
#endif
