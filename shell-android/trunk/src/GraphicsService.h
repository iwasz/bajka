/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GRAPHICSSERVICE_H_
#define GRAPHICSSERVICE_H_

#include <EGL/egl.h>

struct android_app;
class ShellFactory;

/**
 *
 */
class GraphicsService {
public:

        void initDisplay ();
        void termDisplay ();

private:

        GraphicsService (android_app *app);
        friend class ShellFactory;

private:

        android_app *app;
        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;
};

#endif /* GRAPHICSSERVICE_H_ */
