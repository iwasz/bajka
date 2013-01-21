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
#include <util/ShellContext.h>
#include <util/LifecycleHandler.h>
#include "GraphicsService.h"
#include <cassert>
#include "sound/Device.h"
#include <view/openGl/GLContext.h>
#include "EventDispatcher.h"

extern android_app *androidAppInternal (android_app *a);
Core::VariantMap ShellFactory::singletons;

/****************************************************************************/

std::auto_ptr <GameLoop> ShellFactory::createGameLoop (Util::ShellConfig *sConfig, android_app *app)
{
        assert (sConfig);
        assert (app);

        singletons["androidApp"] = Core::Variant (app);
        androidAppInternal (app);
        Util::ShellContext *ctx = createShellContext (sConfig, app);
        Util::LifecycleHandler *handler = createLifecycleHandler ();
        GraphicsService *graphicsService = createGraphicsService (app);
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

        std::auto_ptr <GameLoop> loop = std::auto_ptr <GameLoop> (new GameLoop (ctx, handler, app));
        loop->init ();
        return loop;
}

/****************************************************************************/

Util::ShellContext *ShellFactory::createShellContext (Util::ShellConfig *sConfig, android_app *app)
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

GraphicsService *ShellFactory::createGraphicsService (android_app *app)
{
        return new GraphicsService (app);
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
