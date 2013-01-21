/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ShellFactory.h"
#include "GameLoop.h"
#include <util/BajkaService.h>
#include "ShellContext.h"
#include "LifecycleHandler.h"
#include "GraphicsService.h"
#include <cassert>
#include "sound/Device.h"

extern android_app *androidAppInternal (android_app *a);

/****************************************************************************/

std::auto_ptr <GameLoop> ShellFactory::createGameLoop (Util::ShellConfig *sConfig, android_app *app)
{
        assert (sConfig);
        assert (app);

        androidAppInternal (app);
        ShellContext *ctx = createShellContext (sConfig, app);
        LifecycleHandler *handler = createLifecycleHandler ();
        handler->graphicsService = createGraphicsService (app);
        handler->bajkaService = createBajkaService ();
        ctx->glContext = handler->bajkaService->getGLContext ();
        std::auto_ptr <GameLoop> loop = std::auto_ptr <GameLoop> (new GameLoop (ctx, handler, app));
        loop->init ();
        return loop;
}

/****************************************************************************/

ShellContext *ShellFactory::createShellContext (Util::ShellConfig *sConfig, android_app *app)
{
        ShellContext *ctx = new ShellContext;
//        ctx->app = app;
        ctx->shellConfig = sConfig;
        return ctx;
}

/****************************************************************************/

LifecycleHandler *ShellFactory::createLifecycleHandler ()
{
        LifecycleHandler *handler = new LifecycleHandler;
        return handler;
}

/****************************************************************************/

GraphicsService *ShellFactory::createGraphicsService (android_app *app)
{
        return new GraphicsService (app);
}

/****************************************************************************/

Util::BajkaService *ShellFactory::createBajkaService ()
{
        return new Util::BajkaService ();
}
