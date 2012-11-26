/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ABSTRACTSHELLIMPL_H_
#define BAJKA_ABSTRACTSHELLIMPL_H_

#include "Config.h"
#include "model/IModel.h"
#include "events/EventIdex.h"
#include "events/PointerInsideIndex.h"
#include "events/types/UpdateEvent.h"
#include "view/openGl/GLContext.h"

namespace Model {
class IModelManager;
}

namespace Util {

/**
 * pimpl
 */
struct AbstractShellImpl {

        AbstractShellImpl () : config (NULL),
                model (NULL),
                modelManager (NULL),
                loopActive (true),
                loopPaused (false),
                userData (NULL) {}

        Util::Config *config;
        Model::IModel *model;
        Model::IModelManager *modelManager;
        Event::EventIndex eventIndex;
        Event::PointerInsideIndex pointerInsideIndex;
        bool loopActive;
        bool loopPaused;
        Event::UpdateEvent updateEvent;
        View::GLContext glContext;
        void *userData;
};

}

#endif /* ABSTRACTSHELLIMPL_H_ */
