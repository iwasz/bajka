/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <view/openGl/OpenGl.h>
#include <util/Exceptions.h>
#include "GraphicsService.h"
#include <android_native_app_glue.h>
#include <Platform.h>
#include <util/Config.h>

namespace U = Util;

/****************************************************************************/

GraphicsService::GraphicsService (android_app *a) :
        app (a),
        display (EGL_NO_DISPLAY),
        surface (EGL_NO_SURFACE),
        context (EGL_NO_CONTEXT)
{

}

/****************************************************************************/

bool GraphicsService::initDisplay ()
{
        if (eglGetCurrentContext () != EGL_NO_CONTEXT) {
                return true;
        }

        display = eglGetDisplay (EGL_DEFAULT_DISPLAY);

        if (display == EGL_NO_DISPLAY) {
                throw U::InitException ("eglGetDisplay returned EGL_NO_DISPLAY");
        }

        /*
         * Initializing an already initialized EGL display connection has no effect besides returning the version numbers.
         */
        if (eglInitialize (display, NULL, NULL) == EGL_FALSE) {
                EGLint error = eglGetError ();

                if (error == EGL_BAD_DISPLAY) {
                        throw U::InitException ("eglInitialize returned EGL_BAD_DISPLAY : display is not an EGL display connection.");
                }
                if (error == EGL_NOT_INITIALIZED) {
                        throw U::InitException ("eglInitialize returned EGL_NOT_INITIALIZED : display cannot be initialized.");
                }
        }

        printlog ("GraphicsService::initDisplay : eglInitialize (initialized or re-initialized). app->window=%p.", app->window);

        /*
         * Here specify the attributes of the desired configuration.
         * Below, we select an EGLConfig with at least 8 bits per color
         * component compatible with on-screen windows
         */
        const EGLint attribs[] = {
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                // EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_ALPHA_SIZE, 8,
                EGL_NONE
        };

        // Może być wywołane wielokrotnie
        EGLint numConfigs;
        eglChooseConfig (display, attribs, NULL, 0, &numConfigs);

        if (numConfigs < 1) {
                throw U::InitException ("eglChooseConfig returned 0 configs matching supplied attribList.");
        }

        /*
         * Here, the application chooses the configuration it desires. In this
         * sample, we have a very simplified selection process, where we pick
         * the first EGLConfig that matches our criteria
         */
        EGLConfig config;

        // Może być wywołane wielokrotnie
        if (eglChooseConfig (display, attribs, &config, 1, &numConfigs) == EGL_FALSE) {
                switch (eglGetError ()) {
                case EGL_BAD_DISPLAY:
                        throw U::InitException ("eglChooseConfig returned EGL_BAD_DISPLAY : display is not an EGL display connection.");
                case EGL_BAD_ATTRIBUTE:
                        throw U::InitException ("eglChooseConfig returned EGL_BAD_ATTRIBUTE : attribute_list contains an invalid frame buffer configuration attribute or an attribute value that is unrecognized or out of range.");
                case EGL_NOT_INITIALIZED:
                        throw U::InitException ("eglChooseConfig returned EGL_NOT_INITIALIZED : display has not been initialized.");
                case EGL_BAD_PARAMETER:
                        throw U::InitException ("eglChooseConfig returned EGL_BAD_PARAMETER :   num_config is NULL.");
                }
        }

        // Ta metoda powinna być zawołana najwcześniej z onSurfaceCreated i wtedy app->window nie będzie null.
        if (!app->window) {
                return false;
        }

        /*
         * EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
         * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
         * As soon as we picked a EGLConfig, we can safely reconfigure the
         * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID.
         */
        EGLint format;
        eglGetConfigAttrib (display, config, EGL_NATIVE_VISUAL_ID, &format);
        ANativeWindow_setBuffersGeometry (app->window, 0, 0, format);

        if (this->surface == EGL_NO_SURFACE) {
                EGLSurface surface = eglCreateWindowSurface (display, config, app->window, NULL);

                if (surface == EGL_NO_SURFACE) {
                        throw U::InitException ("eglCreateWindowSurface returned EGL_NO_SURFACE.");
                }

                this->surface = surface;
                printlog ("GraphicsService::initDisplay : eglCreateWindowSurface...");
        }

        if (this->context == EGL_NO_CONTEXT) {
                const EGLint attribList[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
                EGLContext context = eglCreateContext (display, config, NULL, attribList);

                if (context == EGL_NO_CONTEXT) {
                        throw U::InitException ("eglCreateContext returned EGL_NO_CONTEXT.");
                }

                this->context = context;
                printlog ("GraphicsService::initDisplay : eglCreateContext...");
        }

        printlog ("GraphicsService::initDisplay : eglMakeCurrent (%p, %p, %p, %p);", display, surface, surface, context);
        if (eglMakeCurrent (display, surface, surface, context) == EGL_FALSE) {
                throw U::InitException ("eglMakeCurrent failed");
        }

        return true;
}

/****************************************************************************/

void GraphicsService::termDisplay ()
{
        if (this->display != EGL_NO_DISPLAY) {
                if (eglMakeCurrent (this->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) == EGL_FALSE) {
                        throw U::InitException ("eglMakeCurrent failed");
                }

                if (this->context != EGL_NO_CONTEXT) {
                        if (eglDestroyContext (this->display, this->context) == EGL_FALSE) {
                                throw U::InitException ("eglDestroyContext failed");
                        }
                }

                if (this->surface != EGL_NO_SURFACE) {
                        if (eglDestroySurface (this->display, this->surface) == EGL_FALSE) {
                                throw U::InitException ("eglDestroySurface failed");
                        }
                }

                eglTerminate (this->display);
                printlog ("GraphicsService::termDisplay : terminated.");
        }

        this->display = EGL_NO_DISPLAY;
        this->context = EGL_NO_CONTEXT;
        this->surface = EGL_NO_SURFACE;
}

/****************************************************************************/

void GraphicsService::unbindSurfaceAndContext ()
{
        /*
         * When we receive a surfaceDestroyed callback, we must immediately unbind the
         * EGLSurface and EGLContext (eglMakeCurrent with display, NULL, NULL) and
         * must stop rendering.
         *
         */
        if (eglMakeCurrent (display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) == EGL_FALSE) {
                throw U::InitException ("eglMakeCurrent failed");
        }

        if (surface != EGL_NO_SURFACE) {
                if (eglDestroySurface (this->display, this->surface) == EGL_FALSE) {
                        throw U::InitException ("eglDestroySurface failed");
                }
                surface = EGL_NO_SURFACE;
        }

        printlog ("GraphicsService::unbindSurfaceAndContext : done.");
}

/****************************************************************************/

bool GraphicsService::saveScreenDimensionsInConfig (Util::Config *config)
{
        /*
         * Ponieważ ten event lubi pojawiać się w losowych momentach, należy sprawdzić, czy
         * display i surface są OK.
         */
        if (display == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE) {
                return false;
        }

        EGLint w, h;

        if (eglQuerySurface (display, surface, EGL_WIDTH, &w) == EGL_FALSE) {
                throw U::InitException ("eglQuerySurface failed");
        }

        if (eglQuerySurface (display, surface, EGL_HEIGHT, &h) == EGL_FALSE) {
                throw U::InitException ("eglQuerySurface failed");
        }

        config->autoViewport = true;
        config->viewportWidth = w;
        config->viewportHeight = h;

        if (config->autoProjection) {
                config->projectionWidth = w;
                config->projectionHeight = h;
        }

        printlog ("GraphicsService::saveScreenDimensionsInConfig : w=%d, h=%d, autoProjection=%d.", w, h, config->autoProjection);
        return true;
}

/****************************************************************************/

void GraphicsService::swapBuffers ()
{
        eglSwapBuffers (display, surface);
}
