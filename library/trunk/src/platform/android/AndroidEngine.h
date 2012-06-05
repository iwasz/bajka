/*
 * AndroidEngine.h
 *
 *  Created on: May 1, 2012
 *      Author: iwasz
 */

#ifndef ANDROIDENGINE_H_
#define ANDROIDENGINE_H_

#include <android/sensor.h>
#include <EGL/egl.h>
#include "android_native_app_glue.h"
#include "AndroidCmdDispatcher.h"
#include "AndroidInputDispatcher.h"

namespace Util {

struct AndroidEngine {

        AndroidEngine () : androidApp (NULL),
                        display (NULL),
                        surface (NULL),
                        context (NULL),
                        running (false) {}

        struct android_app* androidApp;
        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;
        bool running;
        Event::AndroidCmdDispatcher cmdDispatcher;
        Event::AndroidInputDispatcher inputDispatcher;

};

} /* namespace Util */
#endif /* ANDROIDENGINE_H_ */
