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
#include "GraphicsService.h"

/****************************************************************************/

void LifecycleHandler::onFirstTimeReadyForRender (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onFirstTimeReadyForRender");
        graphicsService->initDisplay ();
}

/****************************************************************************/

void LifecycleHandler::onGainedFocus (ShellContext *ctx, bool firstTime)
{
        printlog ("LifecycleHandler::onGainedFocus");
        graphicsService->initDisplay ();
}

/****************************************************************************/

void LifecycleHandler::onLostFocus (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onLostFocus");

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

}

/****************************************************************************/

void LifecycleHandler::onStop (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onStop");

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

}

/****************************************************************************/

void LifecycleHandler::onStep (ShellContext *ctx, RunningMode r)
{
#ifndef NDEBUG
        static int i = 0;

        if ((++i % 100) == 0) {
                if (r == NORMAL) {
                        printlog ("LifecycleHandler::onStep -> rendering...");
                }
                else if (r == AUTO_PAUSE) {
                        printlog ("LifecycleHandler::onStep -> auto pause...");
                }
                else {
                        printlog ("LifecycleHandler::onStep -> user pause...");
                }
        }
#endif

}

/****************************************************************************/

int32_t LifecycleHandler::onInputEvent (ShellContext *ctx)
{
        printlog ("LifecycleHandler::onInputEvent");
        return 0;
}

