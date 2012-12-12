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

namespace U = Util;

/****************************************************************************/

GraphicsService::GraphicsService (android_app *a) :
        app (a),
        display (NULL),
        surface (NULL),
        context (NULL)
{

}

/****************************************************************************/

void GraphicsService::initDisplay ()
{
        EGLint w, h, format;
        EGLDisplay display = eglGetDisplay (EGL_DEFAULT_DISPLAY);

        if (display == EGL_NO_DISPLAY) {
                throw U::InitException ("eglGetDisplay returned EGL_NO_DISPLAY");
        }

        if (eglInitialize (display, NULL, NULL) == EGL_FALSE) {
                EGLint error = eglGetError ();

                if (error == EGL_BAD_DISPLAY) {
                        throw U::InitException ("eglInitialize returned EGL_BAD_DISPLAY : display is not an EGL display connection.");
                }
                if (error == EGL_NOT_INITIALIZED) {
                        throw U::InitException ("eglInitialize returned EGL_NOT_INITIALIZED : display cannot be initialized.");
                }
        }

        /*
         * Here specify the attributes of the desired configuration.
         * Below, we select an EGLConfig with at least 8 bits per color
         * component compatible with on-screen windows
         */
        const EGLint attribs[] = {
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
//                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_ALPHA_SIZE, 8,
                EGL_NONE
        };


        EGLint numConfigs;
        eglChooseConfig (display, attribs, NULL, 0, &numConfigs);

        if (numConfigs < 1) {
                throw U::InitException ("eglChooseConfig returned 0 configs matching supplied attribList.");
        }

        /* Here, the application chooses the configuration it desires. In this
         * sample, we have a very simplified selection process, where we pick
         * the first EGLConfig that matches our criteria */
        EGLConfig config;

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

        /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
         * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
         * As soon as we picked a EGLConfig, we can safely reconfigure the
         * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
        eglGetConfigAttrib (display, config, EGL_NATIVE_VISUAL_ID, &format);

        printlog ("this->state : %p, this->state->window : %p", app, app->window);
        ANativeWindow_setBuffersGeometry (app->window, 0, 0, format);

        EGLSurface surface = eglCreateWindowSurface (display, config, app->window, NULL);

        if (surface == EGL_NO_SURFACE) {
                throw U::InitException ("eglCreateWindowSurface returned EGL_NO_SURFACE.");
        }

        const EGLint attribList[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        EGLContext context = eglCreateContext (display, config, NULL, attribList);

        if (context == EGL_NO_CONTEXT) {
                throw U::InitException ("eglCreateContext returned EGL_NO_CONTEXT.");
        }

        if (eglMakeCurrent (display, surface, surface, context) == EGL_FALSE) {
                throw U::InitException ("eglMakeCurrent failed");
        }

        eglQuerySurface (display, surface, EGL_WIDTH, &w);
        eglQuerySurface (display, surface, EGL_HEIGHT, &h);

//        TODO!
//        impl->config->autoViewport = true;
//        impl->config->viewportWidth = w;
//        impl->config->viewportHeight = h;

//        if (impl->config->autoProjection) {
//                impl->config->projectionWidth = w;
//                impl->config->projectionHeight = h;
//        }

        this->display = display;
        this->context = context;
        this->surface = surface;

//        TODO
//        impl->glContext.init (impl->config);
}


/****************************************************************************/

void GraphicsService::termDisplay ()
{
        if (this->display != EGL_NO_DISPLAY) {
                eglMakeCurrent (this->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

                if (this->context != EGL_NO_CONTEXT) {
                        eglDestroyContext (this->display, this->context);
                }

                if (this->surface != EGL_NO_SURFACE) {
                        eglDestroySurface (this->display, this->surface);
                }

                eglTerminate (this->display);
        }

        this->display = EGL_NO_DISPLAY;
        this->context = EGL_NO_CONTEXT;
        this->surface = EGL_NO_SURFACE;
}
