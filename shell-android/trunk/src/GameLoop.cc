/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <android/input.h>
#include <android/sensor.h>
#include <android_native_app_glue.h>
#include <Platform.h>
#include "GameLoop.h"
#include "ShellContext.h"
#include "LifecycleHandler.h"
#include <core/Exception.h>
#include <exception>
#include <cstdlib>

/****************************************************************************/

GameLoop::GameLoop (ShellContext *c, LifecycleHandler *h) :
        context (c),
        lifecycleHandler (h),
        autoPause (false),
        suspended (false),
        firstInitWindow (true),
        firstGainedFocus (true),
        savedStatePending (false),
        rendering (false)
{
}

/****************************************************************************/

GameLoop::~GameLoop ()
{
        delete context;
        delete lifecycleHandler;
}

/****************************************************************************/

void GameLoop::init ()
{
        context->app->userData = this;
        context->app->onAppCmd = handleCmd;
        context->app->onInputEvent = handleInput;
}

/****************************************************************************/

void GameLoop::loop ()
{
        try {
                int ident;
                int events;
                struct android_poll_source *source;
                uint32_t lastMs = getCurrentMs ();
                uint32_t deltaMs = 0;

                while (true) {

                        uint32_t currentMs = getCurrentMs ();
                        deltaMs = currentMs - lastMs;
                        lastMs = currentMs;

                        while ((ident = ALooper_pollAll ((suspended) ? (-1) : (0), NULL, &events, (void**)&source)) >= 0) {

                            if (source != NULL) {
                                source->process (context->app, source);
                            }

                //            if (ident == LOOPER_ID_USER) {
                //                if (accelerometerSensor != NULL) {
                //                    ASensorEvent event;
                //                    while (ASensorEventQueue_getEvents (sensorEventQueue, &event, 1) > 0) {
                //                        // LOGI("accelerometer: x=%f y=%f z=%f", event.acceleration.x, event.acceleration.y, event.acceleration.z);
                //                    }
                //                }
                //            }

                            if (context->app->destroyRequested != 0) {
                                // TODO
                                return;
                            }
                        }

                        if (rendering) {
                                lifecycleHandler->onStep (context, autoPause, deltaMs);
                        }
                }
        }
        catch (Core::Exception const &e) {
                printlog ("GameLoop::loop : Core::Exception caught : %s\n", e.getMessage ().c_str ());
                abort ();
        }
        catch (std::exception const &e) {
                printlog ("GameLoop::loop : std::exception caught : %s\n", e.what ());
                abort ();
        }
        catch (...) {
                printlog ("GameLoop::loop : Unknown exception caught");
                abort ();
        }
}

/****************************************************************************/

void GameLoop::handleCmd (android_app *app, int32_t cmd) {
    GameLoop *that = static_cast <GameLoop *> (app->userData);
    that->handleCmd (cmd);
}

/****************************************************************************/

int32_t GameLoop::handleInput (struct android_app* app, AInputEvent *event) {
        GameLoop *that = static_cast <GameLoop *> (app->userData);
        return that->handleInput (event);
}

/****************************************************************************/

void GameLoop::handleCmd (int32_t cmd)
{
        switch (cmd) {
        case APP_CMD_INPUT_CHANGED:
                printlog ("APP_CMD_INPUT_CHANGED");
                break;

        case APP_CMD_INIT_WINDOW:
                printlog ("APP_CMD_INIT_WINDOW");

                if (firstInitWindow) {
                        lifecycleHandler->onFirstTimeReadyForRender (context);
                        firstInitWindow = false;
                }

                rendering = true;
                break;

        case APP_CMD_TERM_WINDOW:
                printlog ("APP_CMD_TERM_WINDOW");
                lifecycleHandler->onSurfaceDestroyed (context);
                rendering = false;
                suspended = true;
                break;

        case APP_CMD_WINDOW_RESIZED:
                printlog ("APP_CMD_WINDOW_RESIZED");
                break;

        case APP_CMD_WINDOW_REDRAW_NEEDED:
                printlog ("APP_CMD_WINDOW_REDRAW_NEEDED");
                break;

        case APP_CMD_CONTENT_RECT_CHANGED:
                printlog ("APP_CMD_CONTENT_RECT_CHANGED");
                break;

        case APP_CMD_GAINED_FOCUS:
                printlog ("APP_CMD_GAINED_FOCUS");
                lifecycleHandler->onGainedFocus (context, firstGainedFocus);
                firstGainedFocus = false;

                if (savedStatePending) {
                        lifecycleHandler->onLoadState (context);
                        savedStatePending = false;
                }

                suspended = false;
                rendering = true;
                break;

        case APP_CMD_LOST_FOCUS:
                printlog ("APP_CMD_LOST_FOCUS");
                if (lifecycleHandler->onLostFocus (context)) {
                        autoPause = true;
                }
                break;

        case APP_CMD_CONFIG_CHANGED:
        {
#if 0
                // Zawsze zwracza zerowy contentRect...
                ARect &r = context->app->contentRect;
                printlog ("viewport.h context->app->contentRect --> %d, %d, %d, %d", r.bottom, r.left, r.right, r.top);
#endif
                printlog ("APP_CMD_CONFIG_CHANGED");
                lifecycleHandler->onConfigChanged (context);
                break;
        }
        case APP_CMD_LOW_MEMORY:
                printlog ("APP_CMD_LOW_MEMORY");
                break;

        case APP_CMD_START:
                printlog ("APP_CMD_START");
                break;

        case APP_CMD_RESUME:
                printlog ("APP_CMD_RESUME");
                break;

        case APP_CMD_SAVE_STATE:
                printlog ("APP_CMD_SAVE_STATE");
                lifecycleHandler->onSaveState (context);
                savedStatePending = true;
                break;

        case APP_CMD_PAUSE:
                printlog ("APP_CMD_PAUSE");
                lifecycleHandler->onPause (context);
                rendering = false;
                suspended = true;
                break;

        case APP_CMD_STOP:
                printlog ("APP_CMD_STOP");
                lifecycleHandler->onStop (context);
                break;

        case APP_CMD_DESTROY:
                printlog ("APP_CMD_DESTROY");
                firstInitWindow = true;
                firstGainedFocus = true;
                lifecycleHandler->onDestroy (context);
                break;

        default:
                printlog ("UNDEFINED CMD");
                break;
        }
}

/****************************************************************************/

int32_t GameLoop::handleInput (AInputEvent *event)
{
        if (rendering) {
                /*
                 * onInputEvent zwróci true, jesli bajka w jakikolwiek zareagowała na event.
                 * False, jeśli nie zareagowała i wówczas event trafi do systemu i zostanie
                 * obsłużony w domyślny sposób.
                 */
                return (int32_t)lifecycleHandler->onInputEvent (context, event);
        }

        return 0;
}
