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

/****************************************************************************/

std::auto_ptr <GameLoop> ShellFactory::createGameLoop (Util::ShellConfig *sConfig)
{
        assert (sConfig);

        ShellContext *ctx = createShellContext (sConfig);
        LifecycleHandler *handler = createLifecycleHandler ();
        handler->graphicsService = createGraphicsService ();
        handler->bajkaService = createBajkaService ();
        ctx->glContext = handler->bajkaService->getGLContext ();
        std::auto_ptr <GameLoop> loop = std::auto_ptr <GameLoop> (new GameLoop (ctx, handler));
        loop->init ();
        return loop;
}

/****************************************************************************/

ShellContext *ShellFactory::createShellContext (Util::ShellConfig *sConfig)
{
        ShellContext *ctx = new ShellContext;
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

GraphicsService *ShellFactory::createGraphicsService ()
{
        return new GraphicsService ();
}

/****************************************************************************/

Util::BajkaService *ShellFactory::createBajkaService ()
{
        return new Util::BajkaService ();
}
