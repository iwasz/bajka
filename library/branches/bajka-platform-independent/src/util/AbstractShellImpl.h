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
                loopActive (true) {}

        Util::Config *config;
        Model::IModel *model;
        Model::IModelManager *modelManager;
        Event::EventIndex eventIndex;
        Event::PointerInsideIndex pointerInsideIndex;
        bool loopActive;
        Event::UpdateEvent updateEvent;
        View::GLContext glContext;
};

}

#endif /* ABSTRACTSHELLIMPL_H_ */
