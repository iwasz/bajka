/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ShellFactory.h"
#include "GameLoop.h"
#include <util/IShell.h>
#include <util/BajkaService.h>
#include "ShellContext.h"
#include "LifecycleHandler.h"
#include "GraphicsService.h"
#include "DataSourceService.h"
#include <cassert>

std::auto_ptr <GameLoop> ShellFactory::createGameLoop (Util::ShellConfig *sConfig, android_app *app)
{
        assert (sConfig);
        assert (app);

        ShellContext *ctx = createShellContext (sConfig, app);
        LifecycleHandler *handler = createLifecycleHandler ();
        handler->graphicsService = createGraphicsService (app);
        handler->dataSourceService = createDataSourceService (app);
        handler->bajkaService = createBajkaService (handler->dataSourceService);
        std::auto_ptr <GameLoop> loop = std::auto_ptr <GameLoop> (new GameLoop (ctx, handler));
        loop->init ();
        return loop;
}

/****************************************************************************/

ShellContext *ShellFactory::createShellContext (Util::ShellConfig *sConfig, android_app *app)
{
        ShellContext *ctx = new ShellContext;
        ctx->app = app;
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

Util::BajkaService *ShellFactory::createBajkaService (Util::IDataSourceService *d)
{
        return new Util::BajkaService (d);
}
/****************************************************************************/

Util::IDataSourceService *ShellFactory::createDataSourceService (android_app *app)
{
        return new DataSourceService (app);
}
