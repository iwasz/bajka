/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID
#include <Container.h>
#include <ContainerFactory.h>
#include <inputFormat/mxml/MXmlMetaService.h>
#include <sstream>

#include <jni.h>
#include <errno.h>

#include <GLES/gl.h>

#include <android/sensor.h>
#include "android_native_app_glue.h"
#include "IModel.h"
#include "draw/Primitives.h"
#include "android/AndroidEngine.h"
#include "App.h"
#include "../../util/Config.h"
#include "Logging.h"

using Util::App;

using namespace Container;
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace E = Event;
namespace G = Geometry;

/**
 * Initialize an EGL context for the current display.
 */
static int engineInitDisplay (App *bajkaApp)
{
        LOGI ("engineInitDisplay");

        // initialize OpenGL ES and EGL
        android_app *androidApp = bajkaApp->getAndroidEngine ()->androidApp;
        Util::AndroidEngine *androidEngine = bajkaApp->getAndroidEngine ();
        Util::Config *bajkaConfig = bajkaApp->getConfig ().get ();

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

        EGLDisplay display = eglGetDisplay (EGL_DEFAULT_DISPLAY);

        eglInitialize (display, 0, 0);

        /* Here, the application chooses the configuration it desires. In this
         * sample, we have a very simplified selection process, where we pick
         * the first EGLConfig that matches our criteria */
        eglChooseConfig (display, attribs, &config, 1, &numConfigs);

        /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
         * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
         * As soon as we picked a EGLConfig, we can safely reconfigure the
         * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
        eglGetConfigAttrib (display, config, EGL_NATIVE_VISUAL_ID, &format);

        ANativeWindow_setBuffersGeometry (androidApp->window, 0, 0, format);

        surface = eglCreateWindowSurface (display, config, androidApp->window, NULL);
        context = eglCreateContext (display, config, NULL, NULL);

        if (eglMakeCurrent (display, surface, surface, context) == EGL_FALSE) {
                LOGW("Unable to eglMakeCurrent");
                return -1;
        }

        eglQuerySurface (display, surface, EGL_WIDTH, &w);
        eglQuerySurface (display, surface, EGL_HEIGHT, &h);

        androidEngine->display = display;
        androidEngine->context = context;
        androidEngine->surface = surface;
        bajkaConfig->setResX (w);
        bajkaConfig->setResY (h);

        // Initialize GL state.
        glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
        glEnable (GL_CULL_FACE);
        glShadeModel (GL_SMOOTH);
        glDisable (GL_DEPTH_TEST);
        glEnableClientState (GL_VERTEX_ARRAY);
        glEnableClientState (GL_COLOR_ARRAY);

        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();

        float aspectRatio = float (h) / w;
        float rX = 100.0;
        float rY = rX * aspectRatio;

        glOrthof (-rX, rX, -rY, rY, -1, 1);
        androidEngine->running = true;

        LOGI ("RES : %d, %d", w, h);

        return 0;
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engineTermDisplay (App *bajkaApp)
{
        Util::AndroidEngine *androidEngine = bajkaApp->getAndroidEngine ();

        if (androidEngine->display != EGL_NO_DISPLAY) {

                eglMakeCurrent (androidEngine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

                if (androidEngine->context != EGL_NO_CONTEXT) {
                        eglDestroyContext (androidEngine->display, androidEngine->context);
                }

                if (androidEngine->surface != EGL_NO_SURFACE) {
                        eglDestroySurface (androidEngine->display, androidEngine->surface);
                }

                eglTerminate (androidEngine->display);
        }

        androidEngine->display = EGL_NO_DISPLAY;
        androidEngine->context = EGL_NO_CONTEXT;
        androidEngine->surface = EGL_NO_SURFACE;
        androidEngine->running = false;
}

/**
 * Process the next input event.
 */
static int32_t engineHandleInput (struct android_app* androidApp, AInputEvent* androidEvent)
{
        App *bajkaApp = static_cast <App *> (androidApp->userData);
        // 0 nieobsłużony przez moją aplikację, 1 obsłużony.
        return bajkaApp->engineHandleInput (androidEvent);
}

/**
 * Process the next main command.
 */
static void engineHandleCmd (struct android_app* androidApp, int32_t cmd)
{
        App *bajkaApp = static_cast <App *> (androidApp->userData);

        switch (cmd) {
        case APP_CMD_INIT_WINDOW:
                // The window is being shown, get it ready.
                if (androidApp->window != NULL) {
                        engineInitDisplay (bajkaApp);
                }

                break;

        case APP_CMD_TERM_WINDOW:
                // The window is being hidden or closed, clean it up.
                engineTermDisplay (bajkaApp);
                break;
        }

        bajkaApp->engineHandleCmd (cmd);
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main (struct android_app* state) {

        std::ostringstream stream;
        LOGI ("Bajka start");
        ContainerFactory factory;

        try {

                app_dummy();

//                Ptr <BeanFactoryContainer> container = ContainerFactory::createContainer (MXmlMetaService::parseAndroidAsset (state->activity->assetManager,  "main.xml"));

                Ptr <MetaContainer> metaContainer = MXmlMetaService::parseAndroidAsset (state->activity->assetManager,  "main.xml");
                Ptr <BeanFactoryContainer> container = factory.createEmptyContainer (metaContainer, true, Ptr <BeanFactoryContainer> (), factory);
                container->addConversion (typeid (Geometry::Point), Geometry::stringToPointVariant);
                container->addConversion (typeid (Geometry::LineString), Geometry::stringToLineStringVariant);
                factory.fill (container, metaContainer);

                Ptr <Util::App> app = vcast <Ptr <Util::App> > (container->getBean ("app"));
                app->setInstance (app.get ());
                app->getAndroidEngine ()->androidApp = state;
                app->init ();

                state->userData = app.get ();
                state->onAppCmd = engineHandleCmd;
                state->onInputEvent = engineHandleInput;

                app->loop ();
                app->destroy ();
        }
        catch (Core::Exception const &e) {
            stream << "Exception caught : \n" << e.getMessage () << std::endl;
        }
        catch (std::exception const &e) {
            stream << "exception caught : " << e.what () << std::endl;
        }
        catch (...) {
            stream << "Unknown exception." << std::endl;
        }

        if (stream) {
            __android_log_print (ANDROID_LOG_FATAL, "bajka", stream.str ().c_str ());
            exit (1);
        }
}
//END_INCLUDE(all)
#endif
