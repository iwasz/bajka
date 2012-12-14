///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include <EGL/egl.h>
//#include <view/openGl/OpenGl.h>
//#include <android_native_app_glue.h>
//#include <android/input.h>
//#include <Platform.h>
//#include <util/AbstractShellImpl.h>
//#include <util/Exceptions.h>
//#include "Shell.h"
//#include "sound/Sound.h"
//#include "common/dataSource/DataSource.h"
//#include "EventDispatcher.h"
//
//namespace M = Model;
//namespace V = View;
//namespace C = Controller;
//namespace E = Event;
//namespace U = Util;
//
///****************************************************************************/
//
//struct Shell::Impl {
//        Impl () : app (NULL),
//                  display (NULL),
//                  surface (NULL),
//                  context (NULL),/*
//                  savedState (NULL)*/
//                  dataSource (NULL)
//        {}
//
//        android_app *app;
//        EGLDisplay display;
//        EGLSurface surface;
//        EGLContext context;
////        struct saved_state savedState;
//        Common::DataSource *dataSource;
//        EventDispatcher dispatcher;
//};
//
///****************************************************************************/
//
//Shell Shell::instance_;
//
//Util::IShell *shell () { return &Shell::instance_; }
//Util::Config *config () { return shell ()->getConfig (); }
//View::GLContext *glContext () { return shell ()->getGLContext (); }
//
//Shell::Shell () : myimpl (new Impl) {}
//Shell::~Shell () { delete myimpl; }
//
///**
// * Process the next input event.
// */
//int32_t handleInput (struct android_app* app, AInputEvent *event) {
//        Shell *shell = static_cast <Shell *> (app->userData);
//        EventDispatcher *dispatcher = static_cast <EventDispatcher *> (shell->getEventDispatcher ());
//        bool ret = false;
//
//        Event::IEvent *e = dispatcher->translate (event, shell->getGLContext ());
//        ret |= dispatcher->dispatch (shell->impl->model, shell->impl->eventIndex, &shell->impl->pointerInsideIndex, e);
//        return ret;
//}
//
///**
// * Process the next main command.
// */
//static void handleCmd (struct android_app* app, int32_t cmd) {
//    Shell *shell = static_cast <Shell *> (app->userData);
//
//    switch (cmd) {
////        case APP_CMD_SAVE_STATE:
////            // The system has asked us to save our current state.  Do so.
////            engine->app->savedState = malloc(sizeof(struct saved_state));
////            *((struct saved_state*)engine->app->savedState) = engine->state;
////            engine->app->savedStateSize = sizeof(struct saved_state);
////            break;
////
//        case APP_CMD_TERM_WINDOW:
//            // The window is being hidden or closed, clean it up.
////            engine_term_display(engine);
//                shell->quit ();
//                break;
////
////        case APP_CMD_GAINED_FOCUS:
////            // When our app gains focus, we start monitoring the accelerometer.
////            if (engine->accelerometerSensor != NULL) {
////                ASensorEventQueue_enableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
////                // We'd like to get 60 events per second (in us).
////                ASensorEventQueue_setEventRate(engine->sensorEventQueue, engine->accelerometerSensor, (1000L/60)*1000);
////            }
////            break;
////
////        case APP_CMD_LOST_FOCUS:
////            // When our app loses focus, we stop monitoring the accelerometer.
////            // This is to avoid consuming battery while not being used.
////            if (engine->accelerometerSensor != NULL) {
////                ASensorEventQueue_disableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
////            }
////            // Also stop animating.
////            engine_draw_frame (engine);
////            break;
//    }
//}
//
///**
// * Data transfer for handleCmdInit
// */
//struct InitWindowDTO {
//
//        InitWindowDTO () : shell (NULL), initDone (false) {}
//
//        Shell *shell;
//        bool initDone;
//};
//
///****************************************************************************/
//
//void handleCmdInit (struct android_app* app, int32_t cmd)
//{
//        InitWindowDTO *initWindowDTO = static_cast <InitWindowDTO *> (app->userData);
//
//        if (cmd != APP_CMD_INIT_WINDOW) {
//                return;
//        }
//
//        if (app->window != NULL) {
//                initWindowDTO->shell->initDisplay ();
//                initWindowDTO->initDone = true;
//        }
//}
//
///****************************************************************************/
//
//void Shell::initDependent ()
//{
//        InitWindowDTO initWindowDTO;
//        initWindowDTO.shell = this;
//
//        myimpl->app = static_cast <android_app *> (impl->userData);
//        myimpl->app->userData = &initWindowDTO;
//        myimpl->app->onAppCmd = handleCmdInit;
//        myimpl->app->onInputEvent = NULL;
//
//        // Read all pending events.
//        int ident;
//        int events;
//        struct android_poll_source* source = NULL;
//
//        while (!initWindowDTO.initDone) {
//                while ((ident = ALooper_pollAll (0, NULL, &events, (void**)&source)) >= 0) {
//                    if (source != NULL) {
//                        source->process (myimpl->app, source);
//                    }
//                }
//
//                delayMs (20);
//        }
//
//        myimpl->app->userData = this;
//        myimpl->app->onAppCmd = handleCmd;
//        myimpl->app->onInputEvent = handleInput;
//
//        myimpl->dispatcher.init (myimpl->app);
//
////        TODO tu można jakoś zapisywac stan - saved_state to jest struktura użytkownika.
////        if (myimpl->state->savedState != NULL) {
////                // We are starting with a previous saved state; restore from it.
////                myimpl->savedState = *(struct saved_state *)myimpl->state->savedState;
////        }
//}
//
///****************************************************************************/
//
//void Shell::initDisplay ()
//{
//        EGLint w, h, format;
//        EGLDisplay display = eglGetDisplay (EGL_DEFAULT_DISPLAY);
//
//        if (display == EGL_NO_DISPLAY) {
//                throw U::InitException ("eglGetDisplay returned EGL_NO_DISPLAY");
//        }
//
//        if (eglInitialize (display, NULL, NULL) == EGL_FALSE) {
//                EGLint error = eglGetError ();
//
//                if (error == EGL_BAD_DISPLAY) {
//                        throw U::InitException ("eglInitialize returned EGL_BAD_DISPLAY : display is not an EGL display connection.");
//                }
//                if (error == EGL_NOT_INITIALIZED) {
//                        throw U::InitException ("eglInitialize returned EGL_NOT_INITIALIZED : display cannot be initialized.");
//                }
//        }
//
//        /*
//         * Here specify the attributes of the desired configuration.
//         * Below, we select an EGLConfig with at least 8 bits per color
//         * component compatible with on-screen windows
//         */
//        const EGLint attribs[] = {
//                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
////                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
//                EGL_BLUE_SIZE, 8,
//                EGL_GREEN_SIZE, 8,
//                EGL_RED_SIZE, 8,
//                EGL_ALPHA_SIZE, 8,
//                EGL_NONE
//        };
//
//
//        EGLint numConfigs;
//        eglChooseConfig (display, attribs, NULL, 0, &numConfigs);
//
//        if (numConfigs < 1) {
//                throw U::InitException ("eglChooseConfig returned 0 configs matching supplied attribList.");
//        }
//
//        /* Here, the application chooses the configuration it desires. In this
//         * sample, we have a very simplified selection process, where we pick
//         * the first EGLConfig that matches our criteria */
//        EGLConfig config;
//
//        if (eglChooseConfig (display, attribs, &config, 1, &numConfigs) == EGL_FALSE) {
//                switch (eglGetError ()) {
//                case EGL_BAD_DISPLAY:
//                        throw U::InitException ("eglChooseConfig returned EGL_BAD_DISPLAY : display is not an EGL display connection.");
//                case EGL_BAD_ATTRIBUTE:
//                        throw U::InitException ("eglChooseConfig returned EGL_BAD_ATTRIBUTE : attribute_list contains an invalid frame buffer configuration attribute or an attribute value that is unrecognized or out of range.");
//                case EGL_NOT_INITIALIZED:
//                        throw U::InitException ("eglChooseConfig returned EGL_NOT_INITIALIZED : display has not been initialized.");
//                case EGL_BAD_PARAMETER:
//                        throw U::InitException ("eglChooseConfig returned EGL_BAD_PARAMETER :   num_config is NULL.");
//                }
//        }
//
//        /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
//         * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
//         * As soon as we picked a EGLConfig, we can safely reconfigure the
//         * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
//        eglGetConfigAttrib (display, config, EGL_NATIVE_VISUAL_ID, &format);
//
//        printlog ("myimpl->state : %p, myimpl->state->window : %p", myimpl->app, myimpl->app->window);
//        ANativeWindow_setBuffersGeometry (myimpl->app->window, 0, 0, format);
//
//        EGLSurface surface = eglCreateWindowSurface (display, config, myimpl->app->window, NULL);
//
//        if (surface == EGL_NO_SURFACE) {
//                throw U::InitException ("eglCreateWindowSurface returned EGL_NO_SURFACE.");
//        }
//
//        const EGLint attribList[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
//        EGLContext context = eglCreateContext (display, config, NULL, attribList);
//
//        if (context == EGL_NO_CONTEXT) {
//                throw U::InitException ("eglCreateContext returned EGL_NO_CONTEXT.");
//        }
//
//        if (eglMakeCurrent (display, surface, surface, context) == EGL_FALSE) {
//                throw U::InitException ("eglMakeCurrent failed");
//        }
//
//        eglQuerySurface (display, surface, EGL_WIDTH, &w);
//        eglQuerySurface (display, surface, EGL_HEIGHT, &h);
//
//        impl->config->autoViewport = true;
//        impl->config->viewportWidth = w;
//        impl->config->viewportHeight = h;
//
//        if (impl->config->autoProjection) {
//                impl->config->projectionWidth = w;
//                impl->config->projectionHeight = h;
//        }
//
//        myimpl->display = display;
//        myimpl->context = context;
//        myimpl->surface = surface;
//
//        impl->glContext.init (impl->config);
//}
//
///****************************************************************************/
//
//void Shell::destroy ()
//{
//        AbstractShell::destroy ();
//
//        if (myimpl->display != EGL_NO_DISPLAY) {
//                eglMakeCurrent (myimpl->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
//
//                if (myimpl->context != EGL_NO_CONTEXT) {
//                        eglDestroyContext (myimpl->display, myimpl->context);
//                }
//
//                if (myimpl->surface != EGL_NO_SURFACE) {
//                        eglDestroySurface (myimpl->display, myimpl->surface);
//                }
//
//                eglTerminate (myimpl->display);
//        }
//
//        myimpl->display = EGL_NO_DISPLAY;
//        myimpl->context = EGL_NO_CONTEXT;
//        myimpl->surface = EGL_NO_SURFACE;
//}
//
///****************************************************************************/
//
//void Shell::swapBuffers ()
//{
//        eglSwapBuffers (myimpl->display, myimpl->surface);
//}
//
///****************************************************************************/
//
//Common::DataSource *Shell::newDataSource ()
//{
//        myimpl->app = static_cast <android_app *> (impl->userData);
//        return new Common::DataSource (myimpl->app->activity->assetManager);
//}
//
///****************************************************************************/
//
//void Shell::deleteDataSource (Common::DataSource *ds)
//{
//        delete ds;
//}
//
///****************************************************************************/
//
//Event::IEventDispather *Shell::getEventDispatcher ()
//{
//        return &myimpl->dispatcher;
//}
