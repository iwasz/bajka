/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cassert>
#include <util/BajkaService.h>
#include <util/ShellContext.h>
#include <util/LifecycleHandler.h>
#include <view/openGl/GLContext.h>
#include "ShellFactory.h"
#include "GameLoop.h"
#include "sound/Device.h"
#include "EventDispatcher.h"
#include "GraphicsService.h"

Core::VariantMap ShellFactory::singletons;

/****************************************************************************/

std::auto_ptr <GameLoop> ShellFactory::createGameLoop (Util::ShellConfig *sConfig)
{
        assert (sConfig);

        Util::ShellContext *ctx = createShellContext (sConfig);
        Util::LifecycleHandler *handler = createLifecycleHandler ();
        GraphicsService *graphicsService = createGraphicsService ();
        handler->setGraphicsService (graphicsService);
        singletons["graphicsService"] = Core::Variant (graphicsService);
        Util::BajkaService *bajkaService = createBajkaService ();
        handler->setBajkaService (bajkaService);
        ctx->glContext = bajkaService->getGLContext ();
        singletons["glContext"] = Core::Variant (ctx->glContext);
        handler->setSingletons (&singletons);
        EventDispatcher *eventDispatcher = createEventDispatcher ();
        handler->setEventDispatcher (eventDispatcher);
        singletons["eventDispatcher"] = Core::Variant (eventDispatcher);

        std::auto_ptr <GameLoop> loop = std::auto_ptr <GameLoop> (new GameLoop (ctx, handler));
        loop->init ();
        return loop;
}

/****************************************************************************/

Util::ShellContext *ShellFactory::createShellContext (Util::ShellConfig *sConfig)
{
        Util::ShellContext *ctx = new Util::ShellContext;
        ctx->shellConfig = sConfig;
        return ctx;
}

/****************************************************************************/

Util::LifecycleHandler *ShellFactory::createLifecycleHandler ()
{
        Util::LifecycleHandler *handler = new Util::LifecycleHandler;
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

/****************************************************************************/

EventDispatcher *ShellFactory::createEventDispatcher ()
{
        return new EventDispatcher;
}
