/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>
#include <cstdlib>

#include <jni.h>
#include <errno.h>
#include <time.h>

#include <EGL/egl.h>
#include <view/openGl/OpenGl.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include <Platform.h>
#include <util/AbstractShellImpl.h>
#include <util/ReflectionMacros.h>
#include <util/Exceptions.h>
#include <view/freetype/Freetype.h>
//#include "GraphicsService.h"
#include "Shell.h"
//#include "EventDispatcher.h"
#include "sound/Sound.h"

namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace E = Event;
namespace U = Util;

/****************************************************************************/

uint32_t getCurrentMs ()
{
        timespec ts;

        if (clock_gettime (CLOCK_MONOTONIC, &ts) == -1) {
                throw U::RuntimeException ("clock_gettime (CLOCK_MONOTONIC) failed");
        }

        return ts.tv_sec * 1000 + ts.tv_nsec / 1000.0;
}

void delayMs (uint32_t ms)
{
        timespec req, res;

        req.tv_sec = ms / 1000;
        req.tv_nsec = (ms % 1000) * 1000;

        if (nanosleep (&req, &res) == -1) {
                throw U::RuntimeException ("nanosleep (&req, &res) failed");
        }
}

int log (const char *format, ...)
{
        va_list args;
        va_start(args, format);
        int ret = __android_log_vprint (ANDROID_LOG_INFO, "bajka", format, args);
        va_end(args);
        return ret;
}

/****************************************************************************/

struct Shell::Impl {
        Impl () : state (NULL),
                  sensorManager (NULL),
                  accelerometerSensor (NULL),
                  sensorEventQueue (NULL),
                  display (NULL),
                  surface (NULL),
                  context (NULL)/*,
                  savedState (NULL)*/ {}

        android_app *state;
        ASensorManager *sensorManager;
        const ASensor *accelerometerSensor;
        ASensorEventQueue *sensorEventQueue;
        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;
//        struct saved_state savedState;
};

/****************************************************************************/

Shell Shell::instance_;

Util::IShell *shell () { return &Shell::instance_; }
Util::Config *config () { return shell ()->getConfig (); }
View::GLContext *glContext () { return shell ()->getGLContext (); }

Shell::Shell () : myimpl (new Impl) {}
Shell::~Shell () { delete myimpl; }

/****************************************************************************/

void Shell::dispatchEvents ()
{
//        myimpl->dispatcher.pollAndDispatch (impl->model, impl->eventIndex, &impl->pointerInsideIndex, getGLContext ());

        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident = ALooper_pollAll (!isPaused () ? 0 : -1, NULL, &events, (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                source->process (myimpl->state, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                if (myimpl->accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents (myimpl->sensorEventQueue, &event, 1) > 0) {
                        // LOGI("accelerometer: x=%f y=%f z=%f", event.acceleration.x, event.acceleration.y, event.acceleration.z);
                    }
                }
            }

            // Check if we are exiting.
            if (myimpl->state->destroyRequested != 0) {
                //engine_term_display (&engine);
                impl->loopActive = false;
                return;
            }
        }
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input (struct android_app* app, AInputEvent* event) {
//    struct engine* engine = (struct engine*)app->userData;
//    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
//        engine->animating = 1;
//        engine->state.x = AMotionEvent_getX(event, 0);
//        engine->state.y = AMotionEvent_getY(event, 0);
//        return 1;
//    }
    return 0;
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd (struct android_app* app, int32_t cmd) {
    Shell *shell = static_cast <Shell *> (app->userData);

    switch (cmd) {
//        case APP_CMD_SAVE_STATE:
//            // The system has asked us to save our current state.  Do so.
//            engine->app->savedState = malloc(sizeof(struct saved_state));
//            *((struct saved_state*)engine->app->savedState) = engine->state;
//            engine->app->savedStateSize = sizeof(struct saved_state);
//            break;
//
//        case APP_CMD_INIT_WINDOW:
//            // The window is being shown, get it ready.
//            if (engine->app->window != NULL) {
//                engine_init_display(engine);
//                engine_draw_frame(engine);
//            }
//            break;
//
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
//            engine_term_display(engine);
                shell->quit ();
                break;
//
//        case APP_CMD_GAINED_FOCUS:
//            // When our app gains focus, we start monitoring the accelerometer.
//            if (engine->accelerometerSensor != NULL) {
//                ASensorEventQueue_enableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
//                // We'd like to get 60 events per second (in us).
//                ASensorEventQueue_setEventRate(engine->sensorEventQueue, engine->accelerometerSensor, (1000L/60)*1000);
//            }
//            break;
//
//        case APP_CMD_LOST_FOCUS:
//            // When our app loses focus, we stop monitoring the accelerometer.
//            // This is to avoid consuming battery while not being used.
//            if (engine->accelerometerSensor != NULL) {
//                ASensorEventQueue_disableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
//            }
//            // Also stop animating.
//            engine_draw_frame (engine);
//            break;
    }
}

/****************************************************************************/

void Shell::init ()
{
        if (TTF_Init () < 0) {
                throw U::InitException ("TTF_Init failed");
        }

        /*
         * Here specify the attributes of the desired configuration.
         * Below, we select an EGLConfig with at least 8 bits per color
         * component compatible with on-screen windows
         */
        const EGLint attribs[] = {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_NONE
        };

        EGLint w, h, format;
        EGLint numConfigs;
        EGLConfig config;
        EGLSurface surface;
        EGLContext context;
        EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

        eglInitialize(display, 0, 0);

        /* Here, the application chooses the configuration it desires. In this
         * sample, we have a very simplified selection process, where we pick
         * the first EGLConfig that matches our criteria */
        eglChooseConfig(display, attribs, &config, 1, &numConfigs);

        /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
         * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
         * As soon as we picked a EGLConfig, we can safely reconfigure the
         * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
        eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

        ANativeWindow_setBuffersGeometry (myimpl->state->window, 0, 0, format);

        surface = eglCreateWindowSurface (display, config, myimpl->state->window, NULL);
        context = eglCreateContext (display, config, NULL, NULL);

        if (eglMakeCurrent (display, surface, surface, context) == EGL_FALSE) {
                throw U::InitException ("eglMakeCurrent failed");
        }

        eglQuerySurface (display, surface, EGL_WIDTH, &w);
        eglQuerySurface (display, surface, EGL_HEIGHT, &h);

        impl->config->autoViewport = true;
        impl->config->viewportWidth = w;
        impl->config->viewportHeight = h;

        if (impl->config->autoProjection) {
                impl->config->projectionWidth = w;
                impl->config->projectionHeight = h;
        }

        myimpl->display = display;
        myimpl->context = context;
        myimpl->surface = surface;

        // Initialize GL state.
        glEnable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        AbstractShell::init ();

        myimpl->state = static_cast <android_app *> (impl->userData);
        myimpl->state->userData = this;
        myimpl->state->onAppCmd = engine_handle_cmd;
        myimpl->state->onInputEvent = engine_handle_input;

        // Prepare to monitor accelerometer
        myimpl->sensorManager = ASensorManager_getInstance ();
        myimpl->accelerometerSensor = ASensorManager_getDefaultSensor (myimpl->sensorManager, ASENSOR_TYPE_ACCELEROMETER);
        myimpl->sensorEventQueue = ASensorManager_createEventQueue (myimpl->sensorManager, myimpl->state->looper, LOOPER_ID_USER, NULL, NULL);

//        TODO tu można jakoś zapisywac stan - saved_state to jest struktura użytkownika.
//        if (myimpl->state->savedState != NULL) {
//                // We are starting with a previous saved state; restore from it.
//                myimpl->savedState = *(struct saved_state *)myimpl->state->savedState;
//        }
}

/****************************************************************************/

void Shell::destroy ()
{
        AbstractShell::destroy ();

        if (myimpl->display != EGL_NO_DISPLAY) {
                eglMakeCurrent (myimpl->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

                if (myimpl->context != EGL_NO_CONTEXT) {
                        eglDestroyContext (myimpl->display, myimpl->context);
                }

                if (myimpl->surface != EGL_NO_SURFACE) {
                        eglDestroySurface (myimpl->display, myimpl->surface);
                }

                eglTerminate (myimpl->display);
        }

        myimpl->display = EGL_NO_DISPLAY;
        myimpl->context = EGL_NO_CONTEXT;
        myimpl->surface = EGL_NO_SURFACE;
}

/****************************************************************************/

void Shell::reset ()
{
        AbstractShell::reset ();
}

/****************************************************************************/

void Shell::swapBuffers ()
{
        eglSwapBuffers (myimpl->display, myimpl->surface);
}
