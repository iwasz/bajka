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

namespace Util {

/**
 * pimpl
 */
struct AbstractShellImpl {

        AbstractShellImpl () : config (NULL),
                model (NULL),
                loopActive (true) {}

        Util::Config *config;
        Model::IModel *model;
        Event::EventIndex eventIndex;
        Event::PointerInsideIndex pointerInsideIndex;
        bool loopActive;
        Event::UpdateEvent updateEvent;
};

}

#endif /* ABSTRACTSHELLIMPL_H_ */