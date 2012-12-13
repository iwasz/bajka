/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LifecycleHandler.h"
#include "ShellContext.h"
#include <Platform.h>
#include <util/BajkaService.h>
#include <util/Scene.h>
#include "GraphicsService.h"
#include "DataSourceService.h"
#include <exception>
#include <Platform.h>
#include <util/Config.h>

/****************************************************************************/

LifecycleHandler::~LifecycleHandler ()
{
        delete graphicsService;
        delete bajkaService;
        delete dataSourceService;
        delete scene;
}

/****************************************************************************/

void LifecycleHandler::onFirstTimeReadyForRender (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onFirstTimeReadyForRender");
        graphicsService->initDisplay ();
        Common::DataSource *ds = dataSourceService->newDataSource ();

        try {
                ctx->config = bajkaService->loadAndOverrideConfig (ds, *ctx->shellConfig);
        }
        catch (std::exception const &e) {
                dataSourceService->deleteDataSource (ds);
                throw;
        }

        dataSourceService->deleteDataSource (ds);
        graphicsService->saveScreenDimensionsInConfig (ctx->config);
        bajkaService->init (ctx->config);
        bajkaService->initProjectionMatrix (ctx->config);

        ds = dataSourceService->newDataSource ();

        try {
                scene = bajkaService->loadScene (ds, *ctx->shellConfig);
        }
        catch (std::exception const &e) {
                dataSourceService->deleteDataSource (ds);
                throw;
        }

        dataSourceService->deleteDataSource (ds);
}

/****************************************************************************/

void LifecycleHandler::onGainedFocus (ShellContext *ctx, bool firstTime)
{
        printlog ("LifecycleHandler::onGainedFocus");
        graphicsService->initDisplay ();

        if (ctx->config) {
                graphicsService->saveScreenDimensionsInConfig (ctx->config);
                bajkaService->initProjectionMatrix (ctx->config);
        }

        // TODO event
}

/****************************************************************************/

bool LifecycleHandler::onLostFocus (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onLostFocus");
        // TODO event i na podstawie wartości zwracanej z niego zwracamu tutaj true (autopauza) lub false (bez autopauzy)
        return true; // true oznacza, ze chcemy wejść w autopauzę.
}

/****************************************************************************/

void LifecycleHandler::onPause (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onPause");

}

/****************************************************************************/

void LifecycleHandler::onSurfaceDestroyed (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onSurfaceDestroyed");
        graphicsService->unbindSurfaceAndContext ();
}

/****************************************************************************/

void LifecycleHandler::onStop (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onStop");
        graphicsService->termDisplay ();
}

/****************************************************************************/

void LifecycleHandler::onDestroy (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onDestroy");

}

/****************************************************************************/

void LifecycleHandler::onSaveState (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onSaveState");

}

/****************************************************************************/

void LifecycleHandler::onLoadState (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onLoadState");

}

/****************************************************************************/

void LifecycleHandler::onConfigChanged (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onConfigChanged");

        if (ctx->config) {
                graphicsService->saveScreenDimensionsInConfig (ctx->config);
                bajkaService->initProjectionMatrix (ctx->config);
        }
}

/****************************************************************************/

void LifecycleHandler::onStep (ShellContext *ctx, bool autoPause)
{
#ifndef NDEBUG
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

        scene->onStep (&updateEvent);
        delayMs (ctx->config->loopDelayMs);
        graphicsService->swapBuffers ();
}

/****************************************************************************/

int32_t LifecycleHandler::onInputEvent (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onInputEvent");
        return 0;
}

