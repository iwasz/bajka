/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LifecycleHandler.h"
#include "Platform.h"
#include "IGraphicsService.h"
#include <exception>
#include "tween/Manager.h"
#include "view/openGl/GLContext.h"
#include "events/IEventDispatcher.h"
#include "util/Config.h"
#include "util/ShellConfig.h"
#include "util/ShellContext.h"
#include "util/BajkaService.h"
#include "util/Scene.h"

namespace Util {

/****************************************************************************/

LifecycleHandler::~LifecycleHandler ()
{
        delete graphicsService;
        delete bajkaService;
        delete scene;
        delete eventDispatcher;
}

/****************************************************************************/

void LifecycleHandler::onFirstTimeReadyForRender (Util::ShellContext *ctx)
{
        printlog ("LifecycleHandler::onFirstTimeReadyForRender");
        ctx->config = bajkaService->loadAndOverrideConfig (*ctx->shellConfig, *singletons);
        printlog ("after bajkaService->loadAndOverrideConfig (*ctx->shellConfig, singletons)");
        graphicsService->initDisplay (ctx->config);
        printlog ("after graphicsService->initDisplay ()");
        graphicsService->saveScreenDimensionsInConfig (ctx->config);
        printlog ("after graphicsService->saveScreenDimensionsInConfig (ctx->config)");
        bajkaService->init (ctx->config);
        printlog ("after bajkaService->init (ctx->config);");
        bajkaService->initProjectionMatrix (ctx->config);
        printlog ("after bajkaService->initProjectionMatrix (ctx->config)");
        scene = bajkaService->loadScene (ctx->shellConfig->definitionFile);
        printlog ("after bajkaService->loadScene (ctx->shellConfig->definitionFile)");
}

/****************************************************************************/

void LifecycleHandler::onGainedFocus (Util::ShellContext *ctx, bool firstTime)
{
        printlog ("LifecycleHandler::onGainedFocus");
        graphicsService->initDisplay (ctx->config);

        if (ctx->config) {
                graphicsService->saveScreenDimensionsInConfig (ctx->config);
                bajkaService->initProjectionMatrix (ctx->config);
        }

        // TODO event
}

/****************************************************************************/

bool LifecycleHandler::onLostFocus (Util::ShellContext *ctx)
{
        printlog ("LifecycleHandler::onLostFocus");
        // TODO event i na podstawie wartości zwracanej z niego zwracamu tutaj true (autopauza) lub false (bez autopauzy)
        return true; // true oznacza, ze chcemy wejść w autopauzę.
}

/****************************************************************************/

void LifecycleHandler::onPause (Util::ShellContext *ctx)
{
        printlog ("LifecycleHandler::onPause");

}

/****************************************************************************/

void LifecycleHandler::onSurfaceDestroyed (Util::ShellContext *ctx)
{
        printlog ("LifecycleHandler::onSurfaceDestroyed");
        graphicsService->unbindSurfaceAndContext ();
}

/****************************************************************************/

void LifecycleHandler::onStop (Util::ShellContext *ctx)
{
        printlog ("LifecycleHandler::onStop");
        graphicsService->termDisplay ();
}

/****************************************************************************/

void LifecycleHandler::onDestroy (Util::ShellContext *ctx)
{
        printlog ("LifecycleHandler::onDestroy");

}

/****************************************************************************/

void LifecycleHandler::onSaveState (Util::ShellContext *ctx)
{
        printlog ("LifecycleHandler::onSaveState");

}

/****************************************************************************/

void LifecycleHandler::onLoadState (Util::ShellContext *ctx)
{
        printlog ("LifecycleHandler::onLoadState");

}

/****************************************************************************/

void LifecycleHandler::onConfigChanged (Util::ShellContext *ctx)
{
        printlog ("LifecycleHandler::onConfigChanged");

        if (ctx->config) {
                graphicsService->saveScreenDimensionsInConfig (ctx->config);
                bajkaService->initProjectionMatrix (ctx->config);
        }
}

/****************************************************************************/

void LifecycleHandler::onStep (Util::ShellContext *ctx, bool autoPause, uint32_t deltaMs)
{
#if 0
        static int i = 0;

        if ((++i % 100) == 0) {
                if (autoPause) {
                        printlog ("LifecycleHandler::onStep -> auto pause...");
                }
                else {
                        printlog ("LifecycleHandler::onStep -> rendering...");
                }
        }
#endif

        updateEvent.setDeltaMs (deltaMs);
        updateEvent.setAutoPause (autoPause);
        scene->onStep (&updateEvent);
        Tween::Manager::getMain ()->update (deltaMs);
        delayMs (ctx->config->loopDelayMs);
        graphicsService->swapBuffers ();
}

/****************************************************************************/

bool LifecycleHandler::onInputEvent (Util::ShellContext *ctx, void *systemEvent)
{
#if 0
        printlog ("LifecycleHandler::onInputEvent");
#endif
        return eventDispatcher->process (systemEvent, scene->getModel (), *scene->getEventIndex (), scene->getPointerInsideIndex (), ctx->glContext);
}

} // nams
